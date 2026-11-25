#ifndef __FILTER_H
#define __FILTER_H

#include "main.h"

typedef struct __filter_TypeDef
{
    float last_value;
    float this_value;
    float diff;
    float output;
}filter_Typedef;


void filter_cal(filter_Typedef* hfilter, float input);
float filter_output(filter_Typedef* filter);



#endif
