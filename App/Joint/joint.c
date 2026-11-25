#include "joint.h"
#include "adc.h"
#include "referee.h"
#include "sucker.h"
#include "potentiometer.h"
#include "string.h"
#include "usart.h"
#include "math.h"

joint_TypeDef joint_group = {0};
referee_pack joint_pack = {0};
uint8_t send_data[22]={0};

void joint_init(void)
{
	joint_group.hadc = &hadc1;
	joint_group.joint_num = 5;

	referee_init(&joint_pack, &huart3);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)joint_group.adc_value, 4);
	
}

void joint_data_make(uint8_t* send_data, joint_TypeDef* joint_group, sucker_TypeDef sucker)
{
	memcpy(send_data, joint_group->angle, (sizeof(float) * joint_group->joint_num));
	send_data[20] = sucker.Move;
	send_data[21] = sucker.Pump_Mode;
}

void vofa_data_send()
{
	static uint8_t vofa_data[24] = {0};
	
	for(int i=0;i<4;i++)
	{
		filter_cal((&joint_group)->filter+i, (&joint_group)->adc_value[i]);
		(&joint_group)->adc_value[i] = filter_output((&joint_group)->filter+i);
		(&joint_group)->vofa_adc[i] = (float)(&joint_group)->adc_value[i];
	}
	
	memcpy(vofa_data, (joint_group).vofa_adc , (sizeof(float) * (joint_group.joint_num)));
	
	vofa_data[20] = 0x00;
	vofa_data[21] = 0x00;
	vofa_data[22] = 0x80;
	vofa_data[23] = 0x7f;

	HAL_UART_Transmit_DMA(&huart3, vofa_data, sizeof(vofa_data));
}

void joint_execute(void)
{
	sucker_rotate_set(&sucker);
	sucker.pump_debounce_count--;

	joint_data_make(send_data, &joint_group, sucker);
 	referee_pack_send(&joint_pack,send_data,22);
	// vofa_data_send();
}

void joint_callback(joint_TypeDef* hjoint, ADC_HandleTypeDef* hadc)
{
	for(int i = 0; i < 4; i++)
	{	
		hjoint->uangle[i] = hjoint->adc_value[i] * 280.0f / 4096.0f;
	}
	joint_angle_make(hjoint);

	HAL_ADC_Start_DMA(hadc, (uint32_t*)hjoint->adc_value, 4);

}

void joint_angle_make(joint_TypeDef* hjoint)
{	
	for(int i=0;i<4;i++)
	{
		filter_cal(hjoint->filter+i, hjoint->uangle[i]);
		hjoint->uangle[i] = filter_output(hjoint->filter+i);
	}
	
	hjoint->angle[0]=-(int)((279-hjoint->uangle[0])*1.09756);
	hjoint->angle[1]=-(int)(hjoint->uangle[1]/1.222222);
	hjoint->angle[2]=(int)(((279-hjoint->uangle[2])*1.0345)*1.7439);
	hjoint->angle[3]=(int)(180-(279-(hjoint->uangle[3])*1.0345));

	if(hjoint->angle[0]<=-120)
	{
		hjoint->angle[0]=-120;		
	}
	if(hjoint->angle[1]<=-135)
	{
		hjoint->angle[1]=-135;		
	}
	if(hjoint->angle[2]>=280*1.7439)
	{
		hjoint->angle[2]=280*1.7439;		
	}
	if(hjoint->angle[3]>=180)
	{
		hjoint->angle[3]=180;			
	}
	
	for(int i=0;i<4;i++)
	{
		hjoint->angle[i]=((float)hjoint->angle[i]/57.3);
	}
}

