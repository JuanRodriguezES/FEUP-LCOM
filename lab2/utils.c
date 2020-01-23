#include <lcom/lcf.h>

#include "i8254.h"
#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (val & 0x00FF);

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = ((val >> 8) & 0x00FF);

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val32;
  if (sys_inb(port, &val32) != 0) {return 3;}
  *value = (val32 & 0x000000FF);

  return 0;
}
