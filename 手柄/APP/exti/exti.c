#include"exti.h"


void My_EXTI_Init()
{
	  
		NVIC_InitTypeDef NVIC_InitStruct;
	  EXTI_InitTypeDef EXTI_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
//	
//	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
		NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	  
	  NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	
	  NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		
//		EXTI_InitStruct.EXTI_Line=EXTI_Line0;
//		EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
//		EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
//		EXTI_InitStruct.EXTI_LineCmd=ENABLE;
//		EXTI_Init(&EXTI_InitStruct);
		
		EXTI_InitStruct.EXTI_Line=EXTI_Line3|EXTI_Line4;
		EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_InitStruct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_InitStruct);
		
		
}
//void EXTI0_IRQHandler(void)                                                          
//{
//		if(EXTI_GetITStatus(EXTI_Line0)==1)
//		{
//				delay_ms(10);
//				if(K_UP==1)
//				{
//						
//				}
//		}
//		EXTI_ClearITPendingBit(EXTI_Line0);
//	
//}

//void EXTI2_IRQHandler(void)                                                          
//{
//		if(EXTI_GetITStatus(EXTI_Line2)==1)
//		{
//				delay_ms(10);
//				if(K_RIGHT==0)
//				{
//						led2=0;
//				}
//		}
//		EXTI_ClearITPendingBit(EXTI_Line2);
//	
//}

//void EXTI3_IRQHandler(void)                                                          
//{
//		if(EXTI_GetITStatus(EXTI_Line3)==1)
//		{
//				delay_ms(10);
//				if(K_RIGHT==0)
//				{
//						if(fre>=20)
//							fre=20;
//				}
//		}
//		EXTI_ClearITPendingBit(EXTI_Line3);
//	
//}

//void EXTI4_IRQHandler(void)                                                          
//{
//		if(EXTI_GetITStatus(EXTI_Line4)==1)
//		{
//				delay_ms(10);
//				if(K_LEFT==0)
//				{
//						fre--;
//					  if(fre<=1)
//							fre=1;
//				}
//		}
//		EXTI_ClearITPendingBit(EXTI_Line4);
//	
//}



