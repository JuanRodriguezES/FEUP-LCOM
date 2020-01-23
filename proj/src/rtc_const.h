#ifndef _LCOM_RTC_CONST_H_
#define _LCOM_RTC_CONST_H_

#include <lcom/lcf.h>

#define RTC_IRQ 8

#define RTC_ADDR_REG 0x70 //WRITE THE ADDRESS OF THE REGISTER
#define RTC_DATA_REG 0x71 //READ/WRITE ONE BYTE FROM/TO RTC

#define RTC_SECONDS 0
#define RTC_MINUTES 2
#define RTC_HOURS 4
#define RTC_WEEK_DAY 6
#define RTC_DAY 7
#define RTC_MONTH 8
#define RTC_YEAR 9

#define RTC_A 10
#define RTC_UIP BIT(7)

#define RTC_B 11
#define RTC_SET BIT(7)
#define RTC_PIE BIT(6)
#define RTC_AIE BIT(5)
#define RTC_UIE BIT(4)

#define RTC_C 12
#define RTC_PF BIT(6)
#define RTC_AF BIT(5)
#define RTC_UF BIT(4)

#define RTC_D 13

#endif
