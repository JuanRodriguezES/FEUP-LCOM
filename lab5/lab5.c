// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>

// Any header files included below this line should have been created by you

#include "graphics_card.h"
#include "graphics_card_const.h"
#include "i8042.h"
#include "kbd.h"

extern uint8_t scancode, stat;

extern vbe_mode_info_t mode_info;

extern unsigned int hres, vres;

extern unsigned int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (set_graphics_card_mode(mode) != 0) {vg_exit(); return 1;}

  sleep(delay);

  if (vg_exit() != 0) {return 1;} //Voltar para o modo de texto

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(1);
  uint8_t bytes[2];
  bool ReadSecond = false;

  if (kbd_subscribe_int(&bit_no)!=0) {return 1;}

  if (set_graphics_card_mode(mode) != 0) {vg_exit(); return 1;}

  if (vg_draw_rectangle(x,y,width,height,color) != 0) {return 1;}

  while(scancode != ESC){
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            if (ReadSecond) {
              ReadSecond = false;
              bytes[1] = scancode;
            }
            else {
              bytes[0] = scancode;
              if (scancode == SIZE) {
                ReadSecond = true;
              }
            }
          }
          break;
        default:
          break; 
      }
    }
  }
  
  
  if (vg_exit() != 0) {return 1;}

  if (kbd_unsubscribe_int()!=0) {return 1;}

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  uint16_t width, height, bot_height, right_width;

  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(1);
  uint8_t bytes[2];
  bool ReadSecond = false;

  if (set_graphics_card_mode(mode) != 0) {vg_exit(); return 1;}

  width = hres / no_rectangles;
  height = vres / no_rectangles;
  bot_height = vres % no_rectangles;
  right_width = hres % no_rectangles;

  for (unsigned int h = 0 ; h < no_rectangles ; h++) {
    
    if (h*height >= (vres - bot_height))
      break;

    for (unsigned int w = 0 ; w < no_rectangles; w++) {
      
      if (w*width >= (hres - right_width))
        break;
      
      if (mode_info.MemoryModel != DIRECT_COLOR_MACRO) {
        vg_draw_rectangle(w*width,h*height,width,height,indexed_color(w,h,step,first, no_rectangles));
      }
      else{
        uint32_t red = R(w,step, first);
        uint32_t green = G(h,step,first);
        uint32_t blue = B(w,h,step,first);
        vg_draw_rectangle(w*width,h*height,width,height, direct_color(red, green, blue));
      }
    }
  }


  if (kbd_subscribe_int(&bit_no)!=0) {return 1;}

  while(scancode != ESC){
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            if (ReadSecond) {
              ReadSecond = false;
              bytes[1] = scancode;
            }
            else {
              bytes[0] = scancode;
              if (scancode == SIZE) {
                ReadSecond = true;
              }
            }
          }
          break;
        default:
          break; 
      }
    }
  }

  if (kbd_unsubscribe_int()!=0) {return 1;}

  if (vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(1);
  uint8_t bytes[2];
  bool ReadSecond = false;

  if (set_graphics_card_mode(0x105) != 0) {vg_exit(); return 1;}

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm,XPM_INDEXED,&img);

  xpm_load(xpm,img.type,&img);

  uint16_t img_height = img.height;
  uint16_t img_width = img.width;

  for (unsigned int height = 0 ; height < img_height ; height++) {
    for (unsigned int width = 0 ; width < img_width; width++) {
      changePixelColor(x+width,y+height,*map);
      map++;
    }
  }
  if (kbd_subscribe_int(&bit_no)!=0) {return 1;}

  while(scancode != ESC){
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            if (ReadSecond) {
              ReadSecond = false;
              bytes[1] = scancode;
            }
            else {
              bytes[0] = scancode;
              if (scancode == SIZE) {
                ReadSecond = true;
              }
            }
          }
          break;
        default:
          break; 
      }
    }
  }

  if (kbd_unsubscribe_int()!=0) {return 1;}

  if (vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t kbd_irq_set = BIT(1);
  uint32_t timer_irq_set = BIT(0);
  uint8_t bytes[2]; 
  bool ReadSecond = false;

  if (set_graphics_card_mode(0x105) != 0) {vg_exit(); return 1;}

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm,XPM_INDEXED,&img);

  xpm_load(xpm,img.type,&img);

  uint16_t img_height = img.height;
  uint16_t img_width = img.width;

  for (unsigned int height = 0 ; height < img_height ; height++) {
    for (unsigned int width = 0 ; width < img_width; width++) {
      changePixelColor(xi+width,yi+height,*map);
      map++;
    }
  }

  uint16_t xnovo = xi, ynovo = yi;
  int frameCounter = 0;
  int timeFrame = sys_hz() / fr_rate;

  if (timer_subscribe_int(&bit_no) != 0) {return 1;}
  if (kbd_subscribe_int(&bit_no)!=0) {return 1;}

  while(scancode != ESC){
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & kbd_irq_set) {
            kbc_ih();
            if (ReadSecond) {
              ReadSecond = false;
              bytes[1] = scancode;
            }
            else {
              bytes[0] = scancode;
              if (scancode == SIZE) {
                ReadSecond = true;
              }
            }
          }
          if (msg.m_notify.interrupts & timer_irq_set && (xnovo != xf || ynovo != yf)) {
            timer_int_handler();
            if (counter % timeFrame == 0) {
              if (speed > 0) {
                vg_draw_rectangle(xnovo,ynovo,img_width,img_height,0);
                if (xi == xf) {
                  if (yi < yf) {
                    if (ynovo + speed > yf)
                      ynovo = yf;
                    else
                      ynovo = ynovo + speed;
                  }
                  else {
                    if (ynovo - speed < yf)
                      ynovo = yf;
                    else
                      ynovo = ynovo - speed;
                  }
                }
                else {
                  if (xi < xf) {
                    if (xnovo + speed > xf)
                      xnovo = xf;
                    else  
                      xnovo = xnovo + speed;
                  }
                  else {
                    if (xnovo - speed < xf)
                      xnovo = xf;
                    else  
                      xnovo = xnovo - speed;
                  }
                }
                map = xpm_load(xpm,XPM_INDEXED,&img);
                for (unsigned int height = 0 ; height < img_height ; height++) {
                  for (unsigned int width = 0 ; width < img_width; width++) {
                    changePixelColor(xnovo + width,ynovo + height,*map);
                    map++;
                  }
                }
              }
              else {
                frameCounter++;
                if (frameCounter % abs(speed) == 0) {
                  vg_draw_rectangle(xnovo,ynovo,img_width,img_height,0);
                  if (xi == xf) {
                    if (yi < yf) {
                      if (ynovo + 1 > yf)
                        ynovo = yf;
                      else
                        ynovo = ynovo + 1;
                    }
                    else {
                      if (ynovo - 1 < yf)
                        ynovo = yf;
                      else
                        ynovo = ynovo - 1;
                    }
                  }
                  else {
                    if (xi < xf) {
                      if (xnovo + 1 > xf)
                        xnovo = xf;
                      else  
                        xnovo = xnovo + 1;
                    }
                    else {
                      if (xnovo - speed < xf)
                        xnovo = xf;
                      else  
                        xnovo = xnovo - 1;
                    }
                  }
                  map = xpm_load(xpm,XPM_INDEXED,&img);
                  for (unsigned int height = 0 ; height < img_height ; height++) {
                    for (unsigned int width = 0 ; width < img_width; width++) {
                      changePixelColor(xnovo + width,ynovo + height,*map);
                      map++;
                    }
                  }
                }
              }
            }
          }
          break;
        default:
          break; 
      }
    }
    
    
  }
  
  if (timer_unsubscribe_int() != 0) {return 1;}
  if (kbd_unsubscribe_int()!=0) {return 1;}

  if (vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_controller)() {
  vg_vbe_contr_info_t info;

  controller_info(&info);

  vg_display_vbe_contr_info(&info);

  return 0;
}
