#include"beep.h"

void BEEP_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;     //
	  RCC_APB2PeriphClockCmd( BEEP_PORT_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin=BEEP_PIN	; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(BEEP_PORT,&GPIO_InitStructure);
}
