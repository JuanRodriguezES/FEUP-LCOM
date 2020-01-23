#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBD_IRQ 1 /* Keyboard IRQ Line */
#define MOUSE_IRQ 12 /* Mouse IRQ Line */

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

//MOUSE

#define LB BIT(0)
#define RB BIT(1)
#define MB BIT(2)
#define MSB_X_DELTA BIT(4)
#define MSB_Y_DELTA BIT(5)
#define X_OVFL BIT(6)
#define Y_OVFL BIT(7)

#define DIS_MOUSE 0xA7
#define WRITE_B_MOUSE 0xD4
#define DIS_DATA_REP 0xF5
#define ENA_DATA_REP 0xF4
#define STREAM_MODE 0xEA
#define REMOTE_MODE 0xF0
#define READ_DATA 0xEB

//Mouse Controller command responses
#define ACK 0xFA   //Acknowledged command or argument
#define NACK 0xFE  //Invalid byte
#define ERROR 0xFC //Second consecutive invalid byte

#endif /* _LCOM_I8042_H */
