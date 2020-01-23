#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "utils3.h"

/*
                  NOTAS
    
    Erro subscribe/unsubscribe: return 1
    Erro kbd_enable: return 2
    Erro irqsetpolicy e irqrmpolicy: return 3
    Erro inb e outb: return 4


    O ficheiro timer.c foi reutilizado, apenas foram utilizadas as funções timer_subscribe_int, timer_unsubscribe_int e timer_int_handler.
    
*/

extern uint8_t scancode, stat;
extern int count_in;
extern unsigned int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int(kbd_test_scan)() {

  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(1);
  uint8_t bytes[2];
  bool ReadSecond = false;


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
              kbd_print_scancode(!(scancode & BREAK), 2, bytes);
            }
            else {
              bytes[0] = scancode;
              if (scancode == SIZE) {
                ReadSecond = true;
              }
              else
                kbd_print_scancode(!(scancode & BREAK), 1, bytes);
            }
            
          }
          break;
        default:
          break; 
      }
    }
  }
  
  if (kbd_unsubscribe_int()!=0) {return 1;}
  kbd_print_no_sysinb(count_in);
  return 0;
}

int(kbd_test_poll)() {
  uint8_t bytes[2];
  bool ReadSecond = false;

  while(scancode != ESC) {
    kbc_ih();

    if (scancode == 0x00) {
      tickdelay(micros_to_ticks(WAIT_KBC));
      continue;
    }

    if (ReadSecond) {
      ReadSecond = false;
      bytes[1] = scancode;
      kbd_print_scancode(!(scancode & BREAK), 2, bytes);
    }
    else {
      bytes[0] = scancode;
      if (scancode == SIZE) {
        ReadSecond = true;
      }
      else
        kbd_print_scancode(!(scancode & BREAK), 1, bytes);
    }
                
    tickdelay(micros_to_ticks(WAIT_KBC));
  }

  if (kbd_enable() != 0) {return 2;}

  kbd_print_no_sysinb(count_in);

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t idletime = n;
  int ipc_status,r;
  message msg;
  uint32_t irq_set_timer = BIT(0); 
  uint32_t irq_set_kbd = BIT(1);
  uint8_t bit_no;
  uint8_t bytes[2];
  bool ReadSecond = false;

  if (kbd_subscribe_int(&bit_no) != 0) {return 1;}
  if (timer_subscribe_int(&bit_no) != 0) {return 1;}

  while(idletime != 0 && scancode != ESC) 
  {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set_kbd) {
              kbc_ih();
              if (ReadSecond) {
                ReadSecond = false;
                bytes[1] = scancode;
                kbd_print_scancode(!(scancode & BREAK), 2, bytes);
              }
              else {
                bytes[0] = scancode;
                if (scancode == SIZE)
                  ReadSecond = true;
                else
                  kbd_print_scancode(!(scancode & BREAK), 1, bytes);
              }
              idletime = n;
              counter = 0;
              continue;
            }
            if (msg.m_notify.interrupts & irq_set_timer) {
              timer_int_handler();
              if (counter % 60 == 0 && counter != 0)
                idletime--;
            }
            break;
          default:
            break; 
      }
    }
  }

  if (timer_unsubscribe_int() != 0) {return 1;}
  if (kbd_unsubscribe_int() != 0) {return 1;}
  kbd_print_no_sysinb(count_in);

  return 0;
}

