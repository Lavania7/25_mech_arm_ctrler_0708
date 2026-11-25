#ifndef __REFEREE_H__
#define __REFEREE_H__
 
#include "main.h"
 
#pragma pack(push, 1)
typedef struct 
{
	uint8_t SOF;
	uint16_t data_length;
	uint8_t seq;
	uint8_t header_crc;
	uint16_t cmd_id;
	uint8_t data[30];
	uint16_t tail_crc;
}referee_pack;

#pragma pack(pop)

extern uint16_t b;

void referee_init(referee_pack* pack, UART_HandleTypeDef *huart);
void referee_pack_send(referee_pack* pack, uint8_t* data, uint16_t length);
#endif
