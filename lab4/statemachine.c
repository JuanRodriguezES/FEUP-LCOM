#include "statemachine.h"

struct mouse_ev mouse_event;
static States state = INIT;
uint8_t xl, yl;

struct mouse_ev * mouse_events(struct packet * pack) {
  static bool lb_pressed = false, rb_pressed = false, mb_pressed = false;

  mouse_event.delta_x = pack->delta_x;
  mouse_event.delta_y = pack->delta_y;

  if (!lb_pressed && pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = true;
    mouse_event.type = LB_PRESSED;
  }
  else if (!rb_pressed && pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = true;
    mouse_event.type = RB_PRESSED;
  }
  else if (lb_pressed && !pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = false;
    mouse_event.type = LB_RELEASED;
  }
  else if (rb_pressed && !pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = false;
    mouse_event.type = RB_RELEASED;
  }
  else if (!mb_pressed && pack->mb) {
    mb_pressed = true;
    mouse_event.type = BUTTON_EV;
  }
  else if(mb_pressed && !pack->mb) {
    mb_pressed = false;
    mouse_event.type = BUTTON_EV;
  }
  else 
    mouse_event.type = MOUSE_MOV;

  return &mouse_event;
}


bool (draw_handler)(uint8_t xlen, uint8_t tolerance, struct packet * pack) {
  
  struct mouse_ev * mouse_event = mouse_events(pack);

  switch (state) {
    case INIT:
      xl = 0; yl = 0;
      if (mouse_event->type == LB_PRESSED)
        state = DRAWUP;
      break;
    case DRAWUP:
      if (mouse_event->type == LB_RELEASED) {
        if (xl >= xlen) {                    
          if (mouse_event->delta_x == 0 || (mouse_event->delta_x != 0 && abs(mouse_event->delta_y/mouse_event->delta_x) > 1))
            state = HALF;
        }
        else 
          state = INIT;
      }                                                      
      else if (mouse_event->type == MOUSE_MOV) { 
        if (mouse_event->delta_x < 0 && abs(mouse_event->delta_x) >= tolerance)
          state = INIT;
        else if (mouse_event->delta_y < 0 && abs(mouse_event->delta_y) >= tolerance)
          state = INIT;                           
        else {
          xl += mouse_event->delta_x;
          yl += mouse_event->delta_y;
        }
      }
      else {
        state = INIT;
      }
      break;
    case HALF:
      xl = 0; yl = 0;
      if (mouse_event->type == RB_PRESSED)
        state = DRAWDOWN;
      else if (mouse_event->type == MOUSE_MOV && abs(mouse_event->delta_x) <= tolerance && abs(mouse_event->delta_y <= tolerance))
        state = HALF;
      else if (mouse_event->type == LB_PRESSED)
        state = DRAWUP;
      else
        state = INIT;
      break;
    case DRAWDOWN:
      if (mouse_event->type == RB_RELEASED) {
        if (xl >= xlen) {
          if (mouse_event->delta_x == 0 || (mouse_event->delta_x != 0 && abs(mouse_event->delta_y/mouse_event->delta_x) > 1))
            return true;
        }
        else 
          state = INIT;
      }
      else if (mouse_event->type == MOUSE_MOV) {
        if (mouse_event->delta_x < 0 && abs(mouse_event->delta_x) >= tolerance) 
          state = INIT;
        else if (mouse_event->delta_y > 0 && abs(mouse_event->delta_y) >= tolerance)
          state = INIT;
        else {
          xl += mouse_event->delta_x;
          yl += mouse_event->delta_y;
        }
      }
      else if (mouse_event->type == LB_PRESSED)
        state = DRAWUP;
      else
        state = INIT;
      break;
  }

  return false;
}

