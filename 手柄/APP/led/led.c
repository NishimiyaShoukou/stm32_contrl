#include"led.h"

void led_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;     //
	  RCC_APB2PeriphClockCmd( LED_PORT_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin=LED_PIN	; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(LED_PORT,&GPIO_InitStructure);
	  GPIO_SetBits(LED_PORT,LED_PIN);
	 

}
