 #include "adc.h"
 #include "SysTick.h"  


#define ADC1_DR_Address ((u32)0x40012400+0x4c)
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3	
static void ADCx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	/*��DMAʱ��*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /*����DMA����*/  
  DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(&(ADC_x->DR));/*ADC�����ݼĴ���*/
  DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)(&adcx);/*�洢����ַ*/
  DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;/*����ΪԴ*/
  DMA_InitStruct.DMA_BufferSize=1;/*���ݵĸ���Ϊ1*/
  DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;/*�����ַ������*/
  DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Disable;/*�洢����ַ������*/
  DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; /*16λ���ݣ������ǰ���*/
  DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;/*������ָ����ѭ����ͣ�ط���*/
  DMA_InitStruct.DMA_Priority=DMA_Priority_High;/*DMA���ȼ���Ϊ��*/
  DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;/*��ʹ�ܴ洢�����洢��*/
	/*������д��Ĵ���*/
  DMA_Init(ADCx_DMA_CHx, &DMA_InitStruct);
	/*ʹ��DMA*/
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
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&(ADC1->DR)); //ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&adcx;//�ڴ��ַ��Ϊ�����׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1; //Ҫ����1������
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; //�ڴ��ַ�̶�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
  ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  		  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
  	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}		


////���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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



























