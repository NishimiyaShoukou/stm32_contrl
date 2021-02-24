#ifndef _ADC_H
#define _ADC_H

#include"system.h"
#include"SysTick.h"

void ADC_Temp_Init(void);
u16 Get_ADC_Temp_Value(u8 ch,u8 times);
int	Get_Temperture(void);


#endif
