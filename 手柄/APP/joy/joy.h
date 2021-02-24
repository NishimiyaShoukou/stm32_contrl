#ifndef _JOY_H_
#define _JOY_H_

#include "system.h"
#include "SysTick.h"

extern float left_joy_x;    //左遥感模拟量
extern float left_joy_y;

extern float right_joy_x;
extern float right_joy_y;
#define LEFTZ   GPIO_Pin_8|GPIO_Pin_7   //数字量输出
#define RIGHTZ   GPIO_Pin_11|GPIO_Pin_12   //数字量输出

#define   left_joy_l1    PAin(7)
#define   left_joy_l2    PAin(8)

#define   right_joy_r1  PAin(11)
#define   right_joy_r2  PAin(12)

void Joy_init(void);  //手柄初始化函数
u16 Get_ADC_Value(u8 ch,u8 times); //采集adc值
void joy_get(void);           //获取遥感值
void DMA_Configuration(void);

#endif



