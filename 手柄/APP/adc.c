 #include "adc.h"
 #include "SysTick.h"  


#define ADC1_DR_Address ((u32)0x40012400+0x4c)
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3	
static void ADCx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	/*打开DMA时钟*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /*配置DMA参数*/  
  DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(&(ADC_x->DR));/*ADC的数据寄存器*/
  DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)(&adcx);/*存储器地址*/
  DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;/*外设为源*/
  DMA_InitStruct.DMA_BufferSize=1;/*数据的个数为1*/
  DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;/*外设地址不增加*/
  DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Disable;/*存储器地址不增加*/
  DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; /*16位数据，所以是半字*/
  DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;/*这里是指数据循环不停地发送*/
  DMA_InitStruct.DMA_Priority=DMA_Priority_High;/*DMA优先级设为高*/
  DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;/*不使能存储器到存储器*/
	/*将参数写入寄存器*/
  DMA_Init(ADCx_DMA_CHx, &DMA_InitStruct);
	/*使能DMA*/
  DMA_Cmd(ADCx_DMA_CHx, ENABLE);
	
}
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	

	/* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&(ADC1->DR)); //ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&adcx;//内存地址变为数组首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1; //要传输1个数据
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; //内存地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准
  ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);	//ADC1,ADC通道,采样时间为239.5周期	  		  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
  	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}		


////获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 



























