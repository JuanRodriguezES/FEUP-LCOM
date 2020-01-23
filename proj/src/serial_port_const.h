#ifndef _LCOM_SERIAL_PORT_CONST_H_
#define _LCOM_SERIAL_PORT_CONST_H_

#include <lcom/lcf.h>

#define VM_CONNECTED 0xFC
#define RECEIVE_VM_CONNECTED 0xFB
#define VM_DISCONNECTED 0xFD
#define MULTIPLAYER_CONNECT 0xFF
#define MULTIPLAYER_DISCONNECT 0xFE

#define SP_COM1 0x3F8
#define SP_COM1_IRQ 4
#define SP_COM2 0x2F8
#define SP_COM2_IRQ 3

#define SP_UART_RBR 0
#define SP_UART_THR 0
#define SP_UART_DLL 0
#define SP_UART_DLM 1
#define SP_UART_IER 1
#define SP_UART_IIR 2
#define SP_UART_FCR 2
#define SP_UART_LCR 3
#define SP_UART_MCR 4
#define SP_UART_LSR 5
#define SP_UART_MSR 6
#define SP_UART_SR  7

//LCR
#define SP_LCR_5BITS            (~BIT(0) & ~BIT(1))
#define SP_LCR_6BITS            (BIT(0) & ~BIT(1))
#define SP_LCR_7BITS            (~BIT(0) & BIT(1))
#define SP_LCR_8BITS            (BIT(0) & BIT(1))
#define SP_LCR_STOPBIT          (BIT(2))
#define SP_LCR_PARITYCONTROL    (BIT(3) & BIT(4) & BIT(5)
#define SP_LCR_ODDPARITY        BIT(3)
#define SP_LCR_BREAKCONTROL     (BIT(6))
#define SP_LCR_DLAB             (BIT(7))

//LSR
#define SP_LSR_RECEIVER                         BIT(0)
#define SP_LSR_OVERRUN_ERROR                    BIT(1)
#define SP_LSR_PARITY_ERROR                     BIT(2)
#define SP_LSR_FRAMING_ERROR                    BIT(3)
#define SP_LSR_BREAK_INT                        BIT(4)
#define SP_LSR_TRANSMITTER_HOLDING_EMPTY        BIT(5)
#define SP_LSR_TRANSMITTER_EMPTY_REGISTER       BIT(6)
#define SP_LSR_FIFO_ERROR                       BIT(7)

//IER
#define SP_IER_RECEIVED_INTERRUPT               BIT(0)
#define SP_IER_TRANSMITTER_INTERRUPT            BIT(1)
#define SP_IER_RECEIVER_LINE_INTERRUPT          BIT(2)
#define SP_IER_MODEM_INTERRUPT                  BIT(3)

//IIR
#define SP_IIR_NO_PENDING_INTERRUPT             BIT(0)
#define SP_IIR_MODEM_STATUS                     (~BIT(1) & ~BIT(2) & ~BIT(3))
#define SP_IIR_TRANSMITTER_HOLDING              (BIT(1) & ~BIT(2) & ~BIT(3))
#define SP_IIR_CHAR_TIMEOUT                     (~BIT(1) & BIT(2) & BIT(3))
#define SP_IIR_RECEIVED_DATA                    (~BIT(1) & BIT(2) & ~BIT(3))
#define SP_IIR_RECEIVER_LINE                    (BIT(1) & BIT(2) & ~BIT(3)) 
#define SP_IIR_64_FIFO_ENABLED                  BIT(5)
#define SP_IIR_FCR_BIT_0                        (BIT(6) & BIT(7))

//FCR
#define SP_FCR_ENABLE_FIFO                      BIT(0)
#define SP_FCR_CLEAR_RECEIVER_FIFO              BIT(1)
#define SP_FCR_CLEAR_TRASMITTER_FIFO            BIT(2)

#endif

