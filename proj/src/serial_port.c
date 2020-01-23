#include "serial_port.h"

int hook_id_sp;

static Queue * transmitQueue;
static Queue * receiveQueue;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (val & 0x00FF);

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = ((val >> 8) & 0x00FF);

  return 0;
}

int sp_set_number_of_bits_per_char(uint8_t number_of_bits) {
  uint32_t lcr;

	if (sys_inb(SP_COM1 + SP_UART_LCR, &lcr) != 0) {return 1;}

  lcr = (lcr & 0xFC) | number_of_bits;

  if (sys_outb(SP_COM1 + SP_UART_LCR, lcr) != 0) {return 1;}

  return 0;
}

int sp_set_parity(uint8_t parity) {
  uint32_t lcr;

	if (sys_inb(SP_COM1 + SP_UART_LCR, &lcr) != 0) {return 1;}

  lcr = (lcr & 0xC7) | parity;

  if (sys_outb(SP_COM1 + SP_UART_LCR, lcr) != 0) {return 1;}

  return 0;
}

int sp_set_bitrate(int bitrate) {
  uint16_t rate = 115200 / bitrate;

  uint8_t ratemsb = 0, ratelsb = 0;
  util_get_LSB(rate, &ratelsb);
  util_get_MSB(rate, &ratemsb);

  //SET DLAB
  uint32_t lcr;
	if (sys_inb(SP_COM1 + SP_UART_LCR, &lcr) != 0) {return 1;}
  lcr = lcr | SP_LCR_DLAB;
  if (sys_outb(SP_COM1 + SP_UART_LCR, lcr) != 0) {return 1;}

  //SET BITRATE
  if (sys_outb(SP_COM1 + SP_UART_DLL, ratelsb) != 0) {return 1;}
  if (sys_outb(SP_COM1 + SP_UART_DLM, ratemsb) != 0) {return 1;}

  //RESET DLAB
  if (sys_inb(SP_COM1 + SP_UART_LCR, &lcr) != 0) {return 1;}
  lcr = lcr & ~SP_LCR_DLAB;
  if (sys_outb(SP_COM1 + SP_UART_LCR, lcr) != 0) {return 1;}

  return 0;
}

int sp_enable_ier(uint8_t macro, bool enable) {
  uint32_t ier;

	if (sys_inb(SP_COM1 + SP_UART_IER, &ier) != 0) {return 1;}

  if (enable)
    ier = ier | macro;
  else 
    ier = ier & ~macro;

  if (sys_outb(SP_COM1 + SP_UART_IER, ier) != 0) {return 1;}

  return 0;
}

int sp_enable_fcr(uint8_t macro, bool enable) {
  uint32_t fcr;

	if (sys_inb(SP_COM1 + SP_UART_FCR, &fcr) != 0) {return 1;}

  if (enable)
    fcr = fcr | macro;
  else
    fcr = fcr & ~macro;

  if (sys_outb(SP_COM1 + SP_UART_FCR, fcr) != 0) {return 1;}

  return 0;
}

int sp_configure_init() {
  //SET 8 BITS PER CHAR
  if (sp_set_number_of_bits_per_char(SP_LCR_8BITS) != 0) {return 1;}

  //SET ODD PARITY
  if (sp_set_parity(SP_LCR_ODDPARITY) != 0) {return 1;}

  //SET BITRATE
  if (sp_set_bitrate(115200) != 0) {return 1;}

  //ENABLE INTERRUPTIONS
  if (sp_enable_ier(SP_IER_RECEIVED_INTERRUPT, true) != 0) {return 1;}
  if (sp_enable_ier(SP_IER_TRANSMITTER_INTERRUPT, true) != 0) {return 1;}
  if (sp_enable_ier(SP_IER_RECEIVER_LINE_INTERRUPT, true) != 0) {return 1;}

  //ENABLE FIFO AND CLEAR TRANSMITTER AND RECEIVER FIFO
  if (sp_enable_fcr(SP_FCR_ENABLE_FIFO, true) != 0) {return 1;}
  if (sp_enable_fcr(SP_FCR_CLEAR_TRASMITTER_FIFO, true) != 0) {return 1;}
  if (sp_enable_fcr(SP_FCR_CLEAR_RECEIVER_FIFO, true) != 0) {return 1;}

  return 0;
}

int sp_configure_end() {
  //DISABLE INTERRUPTIONS
  if (sp_enable_ier(SP_IER_RECEIVED_INTERRUPT, false) != 0) {return 1;}
  if (sp_enable_ier(SP_IER_TRANSMITTER_INTERRUPT, false) != 0) {return 1;}
  if (sp_enable_ier(SP_IER_RECEIVER_LINE_INTERRUPT, false) != 0) {return 1;}

  if (sp_enable_fcr(SP_FCR_ENABLE_FIFO, false) != 0) {return 1;}
  if (sp_enable_fcr(SP_FCR_CLEAR_TRASMITTER_FIFO, true) != 0) {return 1;}
  if (sp_enable_fcr(SP_FCR_CLEAR_RECEIVER_FIFO, true) != 0) {return 1;}


  return 0;
}

int (sp_subscribe_int)(uint8_t *bit_no) {
  hook_id_sp = 4;
  *bit_no = hook_id_sp;

  if (sys_irqsetpolicy(SP_COM1_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id_sp) != 0) {return 3;}

  if (sp_configure_init() != 0) {return 1;}

  transmitQueue = createQueue(128);
  receiveQueue = createQueue(128);

  return 0;
}

int (sp_unsubscribe_int)() {
  if (sp_configure_end() != 0) {return 1;}

  if (sys_irqrmpolicy(&hook_id_sp) != 0) {return 3;}

  while (!queueIsEmpty(receiveQueue)) {
    sp_read();
  }
  free(receiveQueue);
  printf("RECEIVE QUEUE CLEARED. \n");

  while (!queueIsEmpty(transmitQueue)) {
    sp_write();
  }
  free(transmitQueue);
  printf("TRANSMIT QUEUE CLEARED. \n");

  return 0;
}

bool sp_check_write() {
  uint32_t lsr;

  if (sys_inb(SP_COM1 + SP_UART_LSR, &lsr) != 0) {return 1;}

  if ((lsr & SP_LSR_TRANSMITTER_HOLDING_EMPTY) && ~(lsr & SP_LSR_RECEIVER))
    return true;
  else
    return false;
  
}

bool sp_check_read() {
  uint32_t lsr;

  if (sys_inb(SP_COM1 + SP_UART_LSR, &lsr) != 0) {return 1;}

  if (lsr & SP_LSR_RECEIVER)
    return true;
  else
    return false;
}

int sp_write() {
  uint8_t data = 0x00;

  if (!queueIsEmpty(transmitQueue) && sp_check_write()) {
    data = removeFromQueue(transmitQueue);
    if (sys_outb(SP_COM1 + SP_UART_THR, data) != 0) {printf("NOT Sent %x.\n", data);return 1;}
    printf("Sent %x.\n", data);
    //if (queueIsEmpty(transmitQueue))
      //printf("Transmit Queue is now empty.\n");
    return 0;
  }
  else
    return 1;
}

int sp_read() {
  uint32_t rbr;

  if (!sp_check_read())
    return 1;

  if (sp_check_read()) {
    /*
    if (sys_inb(SP_COM1 + SP_UART_RBR, &rbr) != 0) {return 1;}

    *byte = (uint8_t) rbr;

    handle_data(*byte);
    */

    if (sys_inb(SP_COM1 + SP_UART_RBR, &rbr) != 0) {return 1;}

    addToQueue(receiveQueue, (uint8_t)rbr);
    printf("Received %x.\n", (uint8_t)rbr);
    //printf("Added %x to the receive queue.\n", (uint8_t)rbr);
  }
  
  return 0;
}

uint8_t (sp_ih)() {
  uint32_t interruptType = 0x00;
  uint8_t data = 0x00;

  if (sys_inb(SP_COM1 + SP_UART_IIR, &interruptType) != 0) {return 0;}

  //printf("Interrupt Type = 0x%x -> ", interruptType);

  if (interruptType & SP_IIR_NO_PENDING_INTERRUPT)
    return 0;

  if (interruptType & SP_IIR_RECEIVED_DATA) {
    //printf("RECEIVED DATA. Data = ");
    sp_read();
    //printf("%x\n", data);
  }
  else if (interruptType & SP_IIR_TRANSMITTER_HOLDING) {
    //printf("TRANSMITTER HOLDING EMPTY REGISTER.\n");
    sp_write();
  }
  else if (interruptType & SP_IIR_RECEIVER_LINE) {
    printf("\n\nERROR BIT IS 1 ON LSR\n\n");
  }
  else if (interruptType & SP_IIR_MODEM_STATUS) {
    printf("MODEM STATUS.\n");
  }
  else if (interruptType & SP_IIR_CHAR_TIMEOUT) {
    printf("CHARACTER TIMEOUT.\n");
  }

  return data;
}

uint8_t readFromQueue() {
  uint8_t data = 0x00;

  if (!queueIsEmpty(receiveQueue)) {
    data = removeFromQueue(receiveQueue);
    printf("Handled %x.\n", data);
  }

  return data;
}

void addToTransmitQueue(uint8_t data) {
  if (!queueIsFull(transmitQueue)) {
    addToQueue(transmitQueue, data);
    //printf("Added %x to the transmit queue.\n", data);
  }
}

