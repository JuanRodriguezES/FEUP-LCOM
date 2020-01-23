#include "mouse.h"

int hook_id_mouse;
uint8_t scancode;
uint8_t stat;

extern unsigned int hres, vres;
extern xpm_image_t background_menu;

uint16_t convert_2_complement(uint8_t number, uint8_t msb, struct packet * pacote){

  if (pacote->bytes[0] & msb)
    return number - 256;
  return number;

}

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
  hook_id_mouse = MOUSE_IRQ;
  *bit_no = hook_id_mouse;
  if (sys_irqsetpolicy(MOUSE_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id_mouse) != 0) {return 3;}

  return 0;
}

int (mouse_unsubscribe_int)() {
  uint8_t temp;

  if (sys_irqrmpolicy(&hook_id_mouse) != 0) {return 3;}

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

Cursor *cursor;

Cursor * load_cursor() {
  cursor = (Cursor *) malloc(sizeof(Cursor));

  xpm_load(cursor_xpm, XPM_8_8_8_8, &cursor->img);

  cursor->x = 30;
  cursor->y = 30;

  return cursor;
}

void mouse_update(struct packet * pacote) {

  clean_cursor();

  if (pacote->delta_x > 0) {
    if (cursor->x + pacote->delta_x > (int)hres - cursor->img.width)
      cursor->x = (int)hres - cursor->img.width;
    else
      cursor->x += pacote->delta_x;
  }
  else if (pacote->delta_x < 0) {
    if (cursor->x + pacote->delta_x < 0)
      cursor->x = 0;
    else
      cursor->x += pacote->delta_x;
  }
  if (pacote->delta_y < 0) {
    if (cursor->y + cursor->img.height - pacote->delta_y > (int)vres)
      cursor->y = (int)vres - cursor->img.height;
    else
      cursor->y -= pacote->delta_y;
  }
  else if (pacote->delta_y > 0) {
    if (cursor->y - pacote->delta_y < 0)
      cursor->y = 0;
    else
      cursor->y -= pacote->delta_y;
  }

  draw_mouse_cursor();

}

void draw_mouse_cursor() {

  uint32_t* map = (uint32_t*) cursor->img.bytes;

  for(int i = 0; i < cursor->img.width; i++) {
        for (int j = 0; j < cursor->img.height; j++) {
          if (*(map + i + j*cursor->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(cursor->x+i,cursor->y+j,*(map + i + j*cursor->img.width));
    }
  }
}

void clean_cursor() {

  uint32_t* map = (uint32_t*) background_menu.bytes;

  for (int i = cursor->x; i <= cursor->x + cursor->img.width; i++) {
    for (int j = cursor->y; j <= cursor->y + cursor->img.height; j++) {
      if (i < (int)hres - 1 && j < (int)vres - 1)
        changePixelColor(i,j,*(map + i + j * hres));
    }
  }
}

unsigned int check_collision_main_menu () {
  if (cursor->x > 112 && cursor->x < 432 && cursor->y > 400 && cursor->y < 464)
    return 3;
  else if (cursor->x > 560 && cursor->x < 880 && cursor->y > 400 && cursor->y < 464)
    return 4;  
  else if (cursor->x > 112 && cursor->x < 432 && cursor->y > 592 && cursor->y < 656)  
    return 5;
  else if (cursor->x > 560 && cursor->x < 880 && cursor->y > 592 && cursor->y < 656)
    return 1;
  else return 0;
}

unsigned int check_collision_pause_menu () {
  if (cursor->x > 320 && cursor->x < 640 && cursor->y > 400 && cursor->y < 464)
    return 2;
  else if (cursor->x > 320 && cursor->x < 640 && cursor->y > 592 && cursor->y < 656)
    return 1;
  else return 0;
}

unsigned int check_collision_won_menu() {
  if (cursor->x > 320 && cursor->x < 640 && cursor->y > 500 && cursor->y < 564)
    return 1;
  else return 0;
}
