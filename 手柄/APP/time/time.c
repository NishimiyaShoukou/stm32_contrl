#include"time.h"


void TIME4_Init(u16 pre,u16 psc)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		NVIC_InitTypeDef NVIC_InitStruct;
	
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);   //Ê¹ÄÜTIM4Ê±ÖÓ
	
		TIM_TimeBaseInitStructure.TIM_Period=pre;
		TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
		TIM_ITConfig(TIM4,TIM_IT_Update, ENABLE);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	
		TIM_Cmd(TIM4,ENABLE);
	
	
}
  

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==1)
	{
			led4=~led4;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

}

