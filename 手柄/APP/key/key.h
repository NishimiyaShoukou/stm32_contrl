#ifndef _KEY_H
#define _KEY_H

#include"system.h"
#include"SysTick.h"

#define 	KEY_UP_PIN      GPIO_Pin_0
#define   KEY_UP_PORT				GPIOA

#define 	KEY_LEFT_PIN      GPIO_Pin_2
#define 	KEY_DOWN_PIN      GPIO_Pin_3
#define 	KEY_RIGHT_PIN     GPIO_Pin_4
#define   KEY_PORT				GPIOE

#define   K_UP    PAin(0)
#define   K_DOWN  PEin(1)
#define   K_LEFT  PEin(4)
#define   K_RIGHT PEin(3)


//#define   KEY_UP    GPIO_ReadInputDataBit(KEY_UP_PORT, KEY_UP_PIN)
//#define   KEY_DOWN  GPIO_ReadInputDataBit(KEY_PORT, KEY_LEFT_PIN)
//#define   KEY_LEFT  GPIO_ReadInputDataBit(KEY_PORT, KEY_DOWN_PIN)
//#define   KEY_RIGHT GPIO_ReadInputDataBit(KEY_PORT, KEY_RIGHT_PIN)

#define   KEY_UP    1
#define   KEY_DOWN  2
#define   KEY_LEFT  3
#define   KEY_RIGHT 4

void KEY_Init(void);
u8 KEY_Scan(u8 mode);


#endif
