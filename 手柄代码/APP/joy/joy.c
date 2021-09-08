#include"joy.h"

float left_joy_x=2.5;    //��ң��ģ����
float left_joy_y=2.5;

float right_joy_x=2.5;
float right_joy_y=2.5;
u16 ADC_Value[4]={0,0,0,0};
void Joy_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����	
		ADC_InitTypeDef       ADC_InitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	 
		GPIO_InitStructure.GPIO_Pin=LEFTZ; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
		GPIO_InitStructure.GPIO_Pin=RIGHTZ; //
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
		
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_6|GPIO_Pin_3;//ADC
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	//ģ������
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		 GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_6|GPIO_Pin_3);
		ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡ
		
		DMA_Configuration(); 
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;//��ɨ��ģʽ	
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//�ر�����ת��
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ֹ������⣬ʹ���������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
		ADC_InitStructure.ADC_NbrOfChannel =4;//1��ת���ڹ��������� Ҳ����ֻת����������10 
		ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
		
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 4, ADC_SampleTime_239Cycles5);
    // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����     
    ADC_DMACmd(ADC1, ENABLE); 
    /* Enable ADC1 */    
    ADC_Cmd(ADC1, ENABLE);    //ʹ��ָ����ADC1
     /* Enable ADC1 reset calibaration register */      
    ADC_ResetCalibration(ADC1);  //��λָ����ADC1��У׼�Ĵ��� 
    
    /* Enable ADC1 reset calibaration register */      
    ADC_ResetCalibration(ADC1);  //��λָ����ADC1��У׼�Ĵ��� 
    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);  //��ʼָ��ADC1��У׼״̬ 
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1)); 
    //��ȡָ��ADC1��У׼����,����״̬��ȴ�
		DMA_Cmd(DMA1_Channel1,ENABLE);	
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
		
}

u16 Get_ADC_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��,239������,��߲���ʱ�������߾�ȷ��			    
	
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ��ָ����ADC1�����ת����������	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	}
	return temp_val/times;
} 

void DMA_Configuration(void) 
{
    /* ADC1  DMA1 Channel Config */  
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ��DMAʱ��
 
    DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ��ADC1����DMAͨ��1
    DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&(ADC1->DR);  //DMA����ADC����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_Value;      //DMA�ڴ����ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
    DMA_InitStructure.DMA_BufferSize =4;  //��ֵΪ����һ��DMA����Ĵ���
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //��������λ���16λ����DMA����ߴ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //������ѭ������ģʽ��һ�ֽ������Զ���ʼ���ִ���
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��x��ֹ�ڴ浽�ڴ�
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA_InitStruct�в���DMAͨ��
}
void joy_get(void)
{
	left_joy_x=((float)ADC_Value[0]*3.3/4096);
	left_joy_y=((float)ADC_Value[1]*3.3/4096);
	
	right_joy_x=((float)ADC_Value[2]*3.3/4096);
	right_joy_y=((float)ADC_Value[3]*3.3/4096);
//	 left_joy_x=((float)ADC_Value[0]*3.3/4096);
//	left_joy_y=((float)ADC_Value[1]*3.3/4096);
//	
//	right_joy_x=((float)ADC_Value[2]*3.3/4096);
//	right_joy_y=((float)ADC_Value[3]*3.3/4096);
	
}


