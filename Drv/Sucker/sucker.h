#ifndef __SUCKER_H__
#define __SUCKER_H__

#include "main.h"

// 注意在.c里也要同步修改

#define SUCKER_GPIO_BASE GPIOB
#define SUCKER_L_ROLL GPIO_PIN_3
#define SUCKER_R_ROLL GPIO_PIN_3
#define SUCKER_PUMP_PIN GPIO_PIN_3

typedef struct __sucker_TypeDef
{
	uint8_t Move;
	uint8_t Pump_Mode;
	uint8_t pump_debounce_count;
}sucker_TypeDef;
	
void sucker_rotate_set(sucker_TypeDef* hsucker);
void sucker_pump_toggle(sucker_TypeDef* hsucker);
void sucker_pump_callback(sucker_TypeDef* hsucker);

extern sucker_TypeDef sucker;

#endif
