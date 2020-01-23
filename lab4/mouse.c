#include "mouse.h"

int hook_id;
uint8_t scancode;
uint8_t stat;


bool (check_input_buffer)() {
  uint8_t stat;

  if (utils_sys_inb(KBC_CMD_REG, &stat) != 0) {return false;}

  if (stat & IBF) 
    return false;
  else
    return true;
}

bool (check_output_buffer)() {
  uint8_t stat;

  if (utils_sys_inb(KBC_CMD_REG, &stat) != 0) {return false;}

  if (stat & OBF) {
    if ((stat & (PAR_ERR | TO_ERR)) != 0)
      return false;
    else
      return true;
  }
  else
    return false;
  
}

int (mouse_subscribe_int)(uint8_t *bit_no) {
  hook_id = MOUSE_IRQ;
  *bit_no = hook_id;
  if (sys_irqsetpolicy(MOUSE_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id) != 0) {return 3;}

  return 0;
}

int (mouse_unsubscribe_int)() {
  uint8_t temp;

  if (sys_irqrmpolicy(&hook_id) != 0) {return 3;}

  if (utils_sys_inb(KBC_CMD_REG, &stat) != 0) return 4;

  if (stat & OBF)
    if (utils_sys_inb(OUT_BUF, &temp) != 0) return 4;

  return 0;
}

void (mouse_ih)(){
  while (1) {
    if (check_output_buffer()) {
      if (utils_sys_inb(OUT_BUF, &scancode) != 0) {scancode = 0x00;}
      break;
    }
    else {
      scancode = 0x00;
      break;
    }
  }
  
}

void (buildPacket)(struct packet * pacote) {
    
  pacote->lb = pacote->bytes[0] & LB;
  
  pacote->rb = pacote->bytes[0] & RB;

  pacote->mb = pacote->bytes[0] & MB;

  pacote->delta_x = convert_2_complement(pacote->bytes[1],MSB_X_DELTA, pacote);

  pacote->delta_y = convert_2_complement(pacote->bytes[2],MSB_Y_DELTA, pacote);

  pacote->x_ov = pacote->bytes[0] & X_OVFL;

  pacote->y_ov = pacote->bytes[0] & Y_OVFL;

}

int (mouse_enable_data_report)() {
  uint8_t resp;
  uint8_t seconderror = 0;

  do {
    if (sys_outb(KBC_CMD_REG, WRITE_B_MOUSE) != 0) {return 1;}

    if (mouse_write_cmd(ENA_DATA_REP, &resp) != 0) {return 1;}

    if (resp == ACK) {return 0;}
    else if (resp == NACK) {seconderror++;}
    else if (resp == ERROR){return 1;}
    
  } while (seconderror < 2);

  return 1;
}

int (mouse_disable_data_report)() {
  uint8_t resp;
  uint8_t seconderror = 0;

  do {
    if (sys_outb(KBC_CMD_REG, WRITE_B_MOUSE) != 0) {return 1;}

    if (mouse_write_cmd(DIS_DATA_REP, &resp) != 0) {return 1;}

    if (resp == ACK) {return 0;}
    else if (resp == NACK) {seconderror++;}
    else if (resp == ERROR){return 1;}
    
  } while (seconderror < 2);

  return 1;
}

int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp) {
  int count = 0;

  while (count < 3) {

    if (check_input_buffer()) {

      if (sys_outb(WRITE_CMBD, cmd) != 0) {return 1;}

      if (utils_sys_inb(OUT_BUF, resp) != 0) {return 1;}

      return 0;
    }
    
    count++;
  }

  return 1;
}

int (mouse_stream)() {
  uint8_t resp;
  uint8_t seconderror = 0;

  do {
    if (sys_outb(KBC_CMD_REG, WRITE_B_MOUSE) != 0) {return 1;}

    if (mouse_write_cmd(STREAM_MODE, &resp) != 0) {return 1;}

    if (resp == ACK) {return 0;}
    else if (resp == NACK) {seconderror++;}
    else if (resp == ERROR){return 1;}
    
  } while (seconderror < 2);

  return 1;
}

int (mouse_remote)() {
  uint8_t resp;
  uint8_t seconderror = 0;

  do {
    if (sys_outb(KBC_CMD_REG, WRITE_B_MOUSE) != 0) {return 1;}

    if (mouse_write_cmd(REMOTE_MODE, &resp) != 0) {return 1;}

    if (resp == ACK) {return 0;}
    else if (resp == NACK) {seconderror++;}
    else if (resp == ERROR){return 1;}
    
  } while (seconderror < 2);

  return 1;
}

int (mouse_read_data)() {
  uint8_t resp;
  uint8_t seconderror = 0;

  do {
    if (sys_outb(KBC_CMD_REG, WRITE_B_MOUSE) != 0) {return 1;}

    if (mouse_write_cmd(READ_DATA, &resp) != 0) {return 1;}

    if (resp == ACK) {mouse_ih(); return 0;}
    else if (resp == NACK) {seconderror++;}
    else if (resp == ERROR){return 1;}
    
  } while (seconderror < 2);

  return 1;
}
