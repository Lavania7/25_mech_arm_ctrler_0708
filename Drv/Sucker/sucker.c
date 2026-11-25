#include "sucker.h"
#include "joint.h"

// 注意在.h里也要同步修改

#define SUCKER_GPIO_BASE GPIOB
#define SUCKER_L_ROLL GPIO_PIN_3
#define SUCKER_R_ROLL GPIO_PIN_3
#define SUCKER_PUMP_PIN GPIO_PIN_3

sucker_TypeDef sucker = {0};

void sucker_rotate_set(sucker_TypeDef* hsucker)
{
	if(HAL_GPIO_ReadPin(SUCKER_GPIO_BASE, SUCKER_L_ROLL) == GPIO_PIN_SET)
	{
		hsucker->Move = 2;
	}
	else if(HAL_GPIO_ReadPin(SUCKER_GPIO_BASE, SUCKER_R_ROLL) == GPIO_PIN_SET)
	{
		hsucker->Move = 1;
	}
	else
	{
		hsucker->Move = 0;
	}
	
}

void sucker_pump_toggle(sucker_TypeDef* hsucker)
{
	hsucker->Pump_Mode =! hsucker->Pump_Mode;
}

void sucker_pump_callback(sucker_TypeDef* hsucker)
{
	if(hsucker->pump_debounce_count == 0)
	{	
		sucker_pump_toggle(hsucker);
	}
	hsucker->pump_debounce_count = 10;
}
