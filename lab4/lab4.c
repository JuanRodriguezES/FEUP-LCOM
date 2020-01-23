// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "mouse.h"

extern uint8_t scancode;
extern int hook_id;
extern int counter;


uint8_t ms_bytes[3];
struct packet pacote;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(MOUSE_IRQ);
  bool ReadSecond = false, ReadThird = false;


  if (mouse_enable_data_report()!=0) {return 1;}
  if (mouse_subscribe_int(&bit_no)!=0) {return 1;}

  while(cnt > 0){
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set) {
              mouse_ih();
              if (!ReadSecond && !ReadThird && (scancode & BIT(3))){
                ms_bytes[0] = scancode;
                ReadSecond = true;
              }
              else if (ReadSecond) {
                ms_bytes[1] = scancode;
                ReadThird = true;
                ReadSecond = false;
              }
              else if (ReadThird) {
                ms_bytes[2] = scancode;
                ReadThird = false;
                for(unsigned int i = 0; i < 3; i++)
                  pacote.bytes[i] = ms_bytes[i];
                buildPacket(&pacote);
                mouse_print_packet(&pacote);
                cnt--;
              }
              else
                continue;
            }
            break;
          default:
            break; 
        }
      }
  }

  if (mouse_unsubscribe_int()!=0) {return 1;}
  if (mouse_disable_data_report() != 0) {return 1;}
  
  
  return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
  bool ReadSecond = false, ReadThird = false;

  while(cnt > 0) {

    if (mouse_read_data() != 0) {continue;}

    if (!ReadSecond && !ReadThird && (scancode & BIT(3))){
      ms_bytes[0] = scancode;
      ReadSecond = true;
    }
    else if (ReadSecond) {
      ms_bytes[1] = scancode;
      ReadThird = true;
      ReadSecond = false;
    }
    else if (ReadThird) {
      ms_bytes[2] = scancode;
      ReadThird = false;
      for(unsigned int i = 0; i < 3; i++)
        pacote.bytes[i] = ms_bytes[i];
      buildPacket(&pacote);
      mouse_print_packet(&pacote);
      cnt--;
      tickdelay(micros_to_ticks(period*1000));
    }
    else
      continue;
  }

  if (sys_outb(KBC_CMD_REG, OUT_BUF) != 0) {return 4;}
  if (sys_outb(WRITE_CMBD, minix_get_dflt_kbc_cmd_byte()) != 0) {return 4;}

  if (mouse_stream() != 0) {return 1;}
  if (mouse_disable_data_report() != 0) {return 1;}


  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  uint8_t idletime = idle_time;
  int ipc_status,r;
  message msg;
  uint32_t irq_set_timer = BIT(0); 
  uint32_t irq_set_mouse = BIT(MOUSE_IRQ);
  uint8_t bit_no;
  bool ReadSecond = false, ReadThird = false;


  if (mouse_enable_data_report()!=0) {return 1;}
  if (mouse_subscribe_int(&bit_no) != 0) {return 1;}
  if (timer_subscribe_int(&bit_no) != 0) {return 1;}

  while(idletime != 0) 
  {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set_mouse) {
              mouse_ih();
              if (!ReadSecond && !ReadThird && (scancode & BIT(3))){
                ms_bytes[0] = scancode;
                ReadSecond = true;
              }
              else if (ReadSecond) {
                ms_bytes[1] = scancode;
                ReadThird = true;
                ReadSecond = false;
              }
              else if (ReadThird) {
                ms_bytes[2] = scancode;
                ReadThird = false;
                for(unsigned int i = 0; i < 3; i++)
                  pacote.bytes[i] = ms_bytes[i];
                buildPacket(&pacote);
                mouse_print_packet(&pacote);
              }
              
              idletime = idle_time;
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
  if (mouse_unsubscribe_int() != 0) {return 1;}
  if (mouse_disable_data_report()!=0) {return 1;}

  return 0;
}

int (mouse_test_gesture)(uint8_t xlen, uint8_t tolerance) {
  bool done = false;
  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;
  uint32_t irq_set = BIT(MOUSE_IRQ);
  bool ReadSecond = false, ReadThird = false;

  if (mouse_enable_data_report()!=0) {return 1;}
  if (mouse_subscribe_int(&bit_no)!=0) {return 1;}

  while(!done){
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set) {
              mouse_ih();
              if (!ReadSecond && !ReadThird && (scancode & BIT(3))){
                ms_bytes[0] = scancode;
                ReadSecond = true;
              }
              else if (ReadSecond) {
                ms_bytes[1] = scancode;
                ReadThird = true;
                ReadSecond = false;
              }
              else if (ReadThird) {
                ms_bytes[2] = scancode;
                ReadThird = false;
                for(unsigned int i = 0; i < 3; i++)
                  pacote.bytes[i] = ms_bytes[i];
                buildPacket(&pacote);
                mouse_print_packet(&pacote);
                done = draw_handler(xlen, tolerance, &pacote);
              }
              else
                continue;
            }
            break;
          default:
            break; 
        }
      }
  }

  if (mouse_unsubscribe_int()!=0) {return 1;}
  if (mouse_disable_data_report() != 0) {return 1;}
  
  return 0;
}
