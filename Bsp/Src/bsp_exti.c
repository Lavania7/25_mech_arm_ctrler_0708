#include "bsp_exti.h"
#include "sucker.h"
#include "joint.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == SUCKER_PUMP_PIN)
	{
		sucker_pump_callback(&sucker);
	}
}
