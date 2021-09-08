#ifndef _INPUT_H
#define _INPUT_H

#include"system.h"

extern u8 TIM5_CH1_CAPTURE_STA;

extern u16 TIM5_CH1_CAPTURE_VAL;

void TIM5_CH1_Input_Init(u16 pre,u16 psc);


#endif
