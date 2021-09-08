#include"pwm.h"

void TIM3_PWM_CH1_Init(u16 pre,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能TIM3时钟
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(GPIOC,&GPIO_InitStructure);
	  
	
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
		TIM_TimeBaseInitStructure.TIM_Period=pre;
		TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
		
		TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OC1Init(TIM3,&TIM_OCInitStructure); //输出比较通道1初始化  

		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM3,ENABLE);
		
		TIM_Cmd(TIM3,ENABLE);
		

}

