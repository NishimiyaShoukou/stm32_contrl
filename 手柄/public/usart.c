#include "usart.h"

int fputc(int ch,FILE *p)
{
		USART_SendData(USART1,(u8)ch);
	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=1);
	
	  return ch;
}
void USART1_Init(u32 baud)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
		
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9; //TX
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10; //RX
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	  USART_InitStructure.USART_BaudRate=baud;
	  USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1,&USART_InitStructure);
		
		USART_Cmd(USART1, ENABLE);  //使能串口1
		
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启接收中断
//USART_ITConfig(USART1, USART_IT_TC , ENABLE);

		USART_ClearFlag(USART1,USART_FLAG_TC);
		
		
		NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);

}

void USART1_IRQHandler(void)
{
		u8 r;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=0)
		{
				r=USART_ReceiveData(USART1);
				USART_SendData(USART1,r);
			
			  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=1);
				
		}
		USART_ClearFlag(USART1,USART_FLAG_TC);
	
}
