#include "Control_Task.h"
#include "OLED.h"
#include "adc.h"
#include "system.h"
#include "led.h"
#include "usart.h"
#define accur 0.015295//accur=18*3.3/4096��3.3/4096����ADC�������ȣ�18��Ϊ���ò���ת��һ���ܹ���ʾ���ʵ�λ�ӣ�

int32_t adcx;
u32 tick_ms=0;
u8 flag=0;

unsigned char i;
 void Control_task(void)
 {
	  tick_ms++;
		if(tick_ms%20==0)
		{
//			adcx=Get_Adc_Average(ADC_Channel_1,fre);
//			adcx = Get_Adc(ADC_Channel_1);
//		  led1=!led1;
			printf("%d\r\n\r\n",adcx);
		}	

 
 }
