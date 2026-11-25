#include "filter.h"
#include "math.h"

#define THRESHOLD 0.5f
#define ADC_THRE 3

void filter_cal(filter_Typedef* hfilter, float input)
{
    hfilter->this_value = input;
    // 计算当前数据与上一次滤波结果的差值
    float diff = fabs(hfilter->this_value - hfilter->last_value);
    // 如果差值小于阈值，则认为数据稳定，直接使用这一次的滤波结果
    if (diff < ADC_THRE)
	{
        hfilter->output = hfilter->this_value;
    } 
	else 
	{
        // 否则，更新滤波结果
        hfilter->output = hfilter->last_value;
        hfilter->last_value = hfilter->this_value;  // 更新上一次滤波结果
    }
}


float filter_output(filter_Typedef* filter)
{
    return filter->output;
}

