#include "rtc.h"

uint8_t rtc_time[3];
uint8_t rtc_date[3];

int hook_id_rtc;

int inhibit_updates(bool enable) {
  uint32_t regB;
  //READ REGISTER B
  if (sys_outb(RTC_ADDR_REG, RTC_B) != 0){return 1;}
  if (sys_inb(RTC_DATA_REG, &regB) != 0){return 1;}

  if (enable)
    regB = regB | RTC_SET;
  else
    regB = regB & ~RTC_SET;

  //WRITE REGISTER B
  if (sys_outb(RTC_ADDR_REG, RTC_B) != 0){return 1;}
  if (sys_outb(RTC_DATA_REG, regB) != 0){return 1;}
  return 0;
}

int enable_update_interrupts(bool enable) {
  uint32_t regB;

  //READ REGISTER B
  if (sys_outb(RTC_ADDR_REG, RTC_B) != 0){return 1;}
  if (sys_inb(RTC_DATA_REG, &regB) != 0){return 1;}

  if (enable)
    regB = regB | RTC_UIE;
  else
    regB = regB & ~RTC_UIE;

  //WRITE REGISTER B
  if (sys_outb(RTC_ADDR_REG, RTC_B) != 0){return 1;}
  if (sys_outb(RTC_DATA_REG, regB) != 0){return 1;}

  return 0;
}

int (rtc_subscribe_int)(uint8_t *bit_no) {
  hook_id_rtc = 8;
  *bit_no = hook_id_rtc;
  if (sys_irqsetpolicy(RTC_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id_rtc) != 0) {return 3;}

  if (enable_update_interrupts(true) != 0) {return 1;}

  return 0;
}

int (rtc_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id_rtc) != 0) {return 3;}

  if (enable_update_interrupts(false) != 0) {return 1;}

  return 0;
}

void (rtc_ih)() {
  uint32_t regA;

  sys_outb(RTC_ADDR_REG, RTC_C);
  sys_inb(RTC_DATA_REG, &regA);

  if (regA & RTC_UF) {
    if (rtc_time[1] == 59 || rtc_time[1] == 0) {
      rtc_read(RTC_HOURS);
    }
    rtc_read(RTC_MINUTES);
    rtc_read(RTC_SECONDS);
  }
}

int rtc_enable() {
  if (sys_irqenable(&hook_id_rtc) != 0) {return 1;}
  
  return 0;
}

int rtc_disable() {
  if (sys_irqdisable(&hook_id_rtc) != 0) {return 1;}

  return 0;
}

int wait_valid_rtc() {
  uint32_t regA = 0;
  
  do {
    if (rtc_disable() != 0) {return 1;}

    if (sys_outb(RTC_ADDR_REG, RTC_A) != 0) {return 1;}
    if (sys_inb(RTC_DATA_REG, &regA) != 0) {return 1;}

    if (rtc_enable() != 0) {return 1;}

  } while (regA & RTC_UIP);

  return 0;
}

int rtc_read(uint8_t reg) {
  if (wait_valid_rtc() != 0) {return 1;}

  if (reg != RTC_SECONDS && reg != RTC_MINUTES && reg != RTC_HOURS && reg != RTC_DAY && reg != RTC_MONTH && reg != RTC_YEAR) {
    return 1;
  }

  //READ
  uint32_t read;
  if (sys_outb(RTC_ADDR_REG, reg) != 0) {return 1;}
  if (sys_inb(RTC_DATA_REG, &read) != 0) {return 1;}

  switch (reg) {
    case RTC_SECONDS:
      rtc_time[0] = convert_from_bcd((uint8_t) read);
      break;
    case RTC_MINUTES:
      rtc_time[1] = convert_from_bcd((uint8_t) read);
      break;
    case RTC_HOURS:
      rtc_time[2] = convert_from_bcd((uint8_t) read);
      break;
    case RTC_DAY:
      rtc_date[0] = convert_from_bcd((uint8_t) read);
      break;
    case RTC_MONTH:
      rtc_date[1] = convert_from_bcd((uint8_t) read);
      break;
    case RTC_YEAR:
      rtc_date[2] = convert_from_bcd((uint8_t) read);
      break;
    default:
      return 1;
      break;
  }

  return read;
}

uint8_t convert_from_bcd (uint8_t bcdNum) {
  uint8_t decNum = (bcdNum >> 4) * 10;
  decNum += (bcdNum & 0x0F);

  return decNum;
}

void LoadRtc() {
  rtc_read(RTC_DAY);
  rtc_read(RTC_MONTH);
  rtc_read(RTC_YEAR);
  rtc_read(RTC_SECONDS);
  rtc_read(RTC_MINUTES);
  rtc_read(RTC_HOURS);
}
