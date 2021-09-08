#include"input.h"

u8 TIM5_CH1_CAPTURE_STA=0;
u16 TIM5_CH1_CAPTURE_VAL=0;

void TIM5_CH1_Input_Init(u16 pre,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_ICInitTypeDef TIM_ICInitStructure;
		NVIC_InitTypeDef NVIC_InitStruct;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); 
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0	; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	 
	
		TIM_TimeBaseInitStructure.TIM_Period=pre;
		TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
		TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
		TIM_ICInitStructure.TIM_ICFilter=0x00;
		TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
		TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
		TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
		
		TIM_ICInit(TIM5,&TIM_ICInitStructure);
	
		TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1, ENABLE);
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update|TIM_IT_CC1);
		NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	
		TIM_Cmd(TIM5,ENABLE);
	 
}

void TIM5_IRQHandler(void)
{
		if((TIM5_CH1_CAPTURE_STA&0x80)==0)
		{
			if(TIM_GetITStatus(TIM5,TIM_IT_Update)==1)
			{
				if(TIM5_CH1_CAPTURE_STA&0x40)
				{
							if((TIM5_CH1_CAPTURE_STA&0x3f)==0x3f)
							{
									TIM5_CH1_CAPTURE_STA|=0x80;
									TIM5_CH1_CAPTURE_VAL=0xffff;
							}
							else
							{
									TIM5_CH1_CAPTURE_STA++;
							}
				}
			
			}
			if(TIM_GetITStatus(TIM5,TIM_IT_CC1))
			{
	
				 	if(TIM5_CH1_CAPTURE_STA&0x40) 
						{
								TIM5_CH1_CAPTURE_STA|=0x80;
								TIM5_CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
								TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
						}
						else
						{
								TIM5_CH1_CAPTURE_STA=0;
								TIM5_CH1_CAPTURE_VAL=0;
								TIM5_CH1_CAPTURE_STA|=0x40;
								TIM_Cmd(TIM5,DISABLE);
								TIM_SetCounter(TIM5,0);
								TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
								TIM_Cmd(TIM5,ENABLE);
						}
				
			  
			}
		}
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update|TIM_IT_CC1);
}


