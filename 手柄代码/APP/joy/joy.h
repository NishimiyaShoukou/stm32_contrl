#ifndef _JOY_H_
#define _JOY_H_

#include "system.h"
#include "SysTick.h"

extern float left_joy_x;    //��ң��ģ����
extern float left_joy_y;

extern float right_joy_x;
extern float right_joy_y;
#define LEFTZ   GPIO_Pin_8|GPIO_Pin_7   //���������
#define RIGHTZ   GPIO_Pin_11|GPIO_Pin_12   //���������

#define   left_joy_l1    PAin(7)
#define   left_joy_l2    PAin(8)

#define   right_joy_r1  PAin(11)
#define   right_joy_r2  PAin(12)

void Joy_init(void);  //�ֱ���ʼ������
u16 Get_ADC_Value(u8 ch,u8 times); //�ɼ�adcֵ
void joy_get(void);           //��ȡң��ֵ
void DMA_Configuration(void);

#endif



