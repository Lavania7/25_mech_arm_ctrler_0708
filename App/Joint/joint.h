#ifndef __JOINT_H__
#define __JOINT_H__

#include "main.h"
#include "sucker.h"
#include "potentiometer.h"
#include "referee.h"
#include "filter.h"

typedef struct __joint_TypeDef
{
    ADC_HandleTypeDef* hadc;
    uint8_t joint_num;
    uint16_t adc_value[5];
    float vofa_adc[5];
    float uangle[5];
    float angle[5];
    filter_Typedef filter[5];
}joint_TypeDef;

void joint_init(void);
void joint_execute(void);
void joint_callback(joint_TypeDef* hjoint_group, ADC_HandleTypeDef* hadc);
void joint_angle_make(joint_TypeDef* hjoint);

void joint_data_make(uint8_t* send_data, joint_TypeDef* joint_group, sucker_TypeDef sucker);

extern joint_TypeDef joint_group;

#endif
