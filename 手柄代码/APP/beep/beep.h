#ifndef _BEEP_H
#define _BEEP_H

#include"system.h"
void BEEP_Init(void);
#define BEEP_PORT_RCC    RCC_APB2Periph_GPIOB
#define BEEP_PIN				 GPIO_Pin_5
#define BEEP_PORT				 GPIOB

#define beep PBout(5)

#endif
