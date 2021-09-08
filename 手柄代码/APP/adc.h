#ifndef _ADC_H
#define _ADC_H	
#include "system.h"
 
#include "Control_Task.h"
void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times);
static void ADCx_DMA_Config(void);
/*ADC*/
#define ADC_x							ADC1
#define ADCx_CLK  		    RCC_APB2Periph_ADC1
#define ADCx_CHx 		    	ADC_Channel_1

/*DMA*/
#define ADCx_DMA_CLK  		RCC_AHBPeriph_DMA1
#define ADCx_DMA_CHx 		  DMA1_Channel1
#endif 
