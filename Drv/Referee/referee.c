#include "referee.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"
#include "crc.h"

UART_HandleTypeDef* referee_huart;
uint16_t b = 0;
void referee_init(referee_pack* pack, UART_HandleTypeDef *huart)
{
	referee_huart = huart;
	pack->SOF = 0xA5;
	pack->data_length = 30;
	pack->seq = 0;
	pack->cmd_id = 0x0302;
}

void referee_pack_send(referee_pack* pack, uint8_t* data, uint16_t length)
{
	pack->seq ++;
	pack->header_crc = crc8((uint8_t*)pack, 4);
	memcpy(pack->data, data, length);
	//memset(((uint8_t*)pack)+14,0,16);
	b = Get_CRC16_Check_Sum((uint8_t*)pack,37);
	*(((uint8_t*)pack)+(sizeof(referee_pack) - 2)) = (uint8_t) b & 0x00FF;
	*(((uint8_t*)pack)+(sizeof(referee_pack) - 1)) = (uint8_t)( b & 0xFF00 )>> 8;
	
	HAL_UART_Transmit_DMA(referee_huart,(uint8_t*)pack, sizeof(referee_pack));
}

void pack_make()
{
//	e1.a = 1;
//	e2.b = 1;
//	t1 = sizeof(e1);
//	t2 = sizeof(e2);
//	pack[0]=0xA5;
//	pack[1]=(uint16_t)sizeof(custom_robot_data_t_0.data);
//	pack[2]=(uint16_t)sizeof(custom_robot_data_t_0.data);
//	pack[3]=Seq;
//	pack[4]=crc8(pack,4);
//	pack[5]=0x02;
//	pack[6]=0x03;
//	
}
	
