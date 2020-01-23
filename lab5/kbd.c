#include "kbd.h"

uint8_t scancode, count_in;
uint8_t stat;

int hook_id;

int (kbd_subscribe_int)(uint8_t *bit_no) {
  hook_id = 1;
  *bit_no = hook_id;
  if (sys_irqsetpolicy(KBD_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id) != 0) {return 3;}

  return 0;
}

int (kbd_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != 0) {return 3;}

  return 0;
}

int (utils_sys_inb)(int port, uint8_t *value) {
  uint32_t val32;
  if (sys_inb(port, &val32) != 0) {return 4;}
  *value = (val32 & 0x000000FF);
  count_in++;

  return 0;
}

void (kbc_ih)(){
  while( 1 )
  {
    if (utils_sys_inb(STAT_REG, &stat) != 0) {scancode = 0x00;}
    /*assuming it returns OK*//*loop while 8042 output buffer is empty*/
    
    if (stat & OBF) {
      if (utils_sys_inb(OUT_BUF, &scancode) != 0) {scancode = 0x00;} /*assuming it returns OK*/
      if ((stat & (PAR_ERR | TO_ERR)) != 0 )
        scancode = 0x00;
        break;
    }
  }
}

int (kbd_enable)() {
  uint8_t command_byte;

  if (sys_outb(KBC_CMD_REG, READ_CMDB) != 0) {return 4;}

  if (utils_sys_inb(OUT_BUF, &command_byte) != 0) {return 4;}

  command_byte = (command_byte | INT);

  if (sys_outb(KBC_CMD_REG, OUT_BUF) != 0) {return 4;}

  if (sys_outb(WRITE_CMBD, command_byte) != 0) {return 4;}

  return 0;
}

