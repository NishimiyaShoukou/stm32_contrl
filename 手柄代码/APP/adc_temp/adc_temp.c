#include"adc_temp.h"

void ADC_Temp_Init()
{
		ADC_InitTypeDef  ADC_InitStructure; 
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
		ADC_TempSensorVrefintCmd(ENABLE);
	
		ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode=DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel=1;
	
		ADC_Init(ADC1,&ADC_InitStructure);
	
		ADC_Cmd(ADC1, ENABLE);
	
		
}

u16 Get_ADC_Temp_Value(u8 ch,u8 times)
{
		u8 t;
	  u32 temp_val=0;
		ADC_RegularChannelConfig(ADC1,ch ,1,ADC_SampleTime_239Cycles5);
		for(t=0;t<times;t++)
		{
					ADC_SoftwareStartConvCmd(ADC1,ENABLE);
					while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC ));
					temp_val+=ADC_GetConversionValue(ADC1);
					delay_ms(5);
			
		}
		return temp_val/times;
}

int	Get_Temperture(void)
{
		u16 adc_value=0;
		double temperture=0;
		int temp;
		adc_value=Get_ADC_Temp_Value(ADC_Channel_16,10);
		temperture=(double)adc_value*(3.3/4095);
		temperture=(1.43-temperture)/0.0043+25;
		temp=temperture*100;
		return temp;
}


