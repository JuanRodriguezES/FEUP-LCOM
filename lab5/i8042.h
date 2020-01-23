#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBD_IRQ 1 /* Keyboard IRQ Line */

/* I/O port addresses */

#define STAT_REG 0x64 /**< @brief Register for status */
#define KBC_CMD_REG 0x64
#define OBF BIT(0)
#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)
#define WAIT_KBC 20000

#define OUT_BUF 0x60
#define BREAK BIT(7)
#define SIZE 0xE0
#define ESC 0x81
#define IBF BIT(1)

#define READ_CMDB 0x20
#define WRITE_CMBD 0x60

#define MASK_IBF 0xFD

#define INT BIT(0) //Interrupt enable for keyboard in Command Byte

#endif /* _LCOM_I8042_H */
