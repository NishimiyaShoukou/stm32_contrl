#ifndef _RTC_H
#define _RTC_H

#include"system.h"

#include"SysTick.h"
#include"usart.h"

typedef struct
{
		u8 hour;
		u8 min;
		u8 sec;
	
}_calendar;

u8 RTC_Init(void);

void RTC_Get(void);
extern _calendar calendar;

#endif
