#ifndef _smg_H
#define _smg_H
#include"system.h"

#define SMG_PORT_RCC    RCC_APB2Periph_GPIOC
#define SMG_PIN				 (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define SMG_PORT				GPIOC

void SMG_Init(void);

#endif
