#include "bsp_tim.h"
#include "tim.h"
#include "joint.h"

void bsp_tim_init(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
	  joint_execute();
  }
}
