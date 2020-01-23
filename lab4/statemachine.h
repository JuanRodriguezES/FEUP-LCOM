#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

typedef enum {INIT, DRAWUP, HALF, DRAWDOWN} States;

struct mouse_ev * mouse_events(struct packet * pack);

//bool (move_handler)(uint8_t tolerance, bool up, struct mouse_ev * mouse_event);

bool (draw_handler)(uint8_t xlen, uint8_t tolerance, struct packet * pack);
