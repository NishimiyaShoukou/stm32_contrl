#ifndef _led_H
#define _led_H
#include"system.h"


void led_Init(void);
#define LED_PORT_RCC    RCC_APB2Periph_GPIOC
#define LED_PIN				 GPIO_Pin_13
#define LED_PORT				GPIOC

#define led PCout(13)


#endif
