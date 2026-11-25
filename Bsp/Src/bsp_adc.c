#include "bsp_adc.h"
#include "adc.h"
#include "joint.h"

void bsp_adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1)
	{
		joint_callback(&joint_group, hadc);
	}
	
}
