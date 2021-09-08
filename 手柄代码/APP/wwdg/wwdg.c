#include "wwdg.h"

void WWDG_Init()
{
		NVIC_InitTypeDef NVIC_InitStruct;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
		WWDG_SetWindowValue(0x5F);
		WWDG_SetPrescaler(WWDG_Prescaler_8);

		NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		WWDG_Enable(0x7F);
		WWDG_ClearFlag();
		WWDG_EnableIT();
}

void WWDG_IRQHandler()
{
		WWDG_SetCounter(0x7F);
		WWDG_ClearFlag();
		led2=!led2;
		
}




