#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

int (utils_sys_inb)(int port, uint8_t *value);

void (kbc_ih)();

int (kbd_enable)();
