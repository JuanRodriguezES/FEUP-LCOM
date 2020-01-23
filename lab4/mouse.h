#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "utils4.h"
#include "statemachine.h"

bool (check_input_buffer)();

bool (check_output_buffer)();

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (buildPacket)(struct packet * pacote);

int (mouse_enable_data_report)();

int (mouse_disable_data_report)();

int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp);

int (mouse_stream)();

int (mouse_remote)();

int (mouse_read_data)();
