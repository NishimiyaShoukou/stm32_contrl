#include"joy.h"

float left_joy_x=2.5;    //左遥感模拟量
float left_joy_y=2.5;

float right_joy_x=2.5;
float right_joy_y=2.5;
u16 ADC_Value[4]={0,0,0,0};
void Joy_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
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
		
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_6|GPIO_Pin_3;//ADC
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	//模拟输入
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		 GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_6|GPIO_Pin_3);
		ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省
		
		DMA_Configuration(); 
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;//非扫描模式	
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//关闭连续转换
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//禁止触发检测，使用软件触发
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
		ADC_InitStructure.ADC_NbrOfChannel =4;//1个转换在规则序列中 也就是只转换规则序列10 
		ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
		
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_239Cycles5 );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 4, ADC_SampleTime_239Cycles5);
    // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）     
    ADC_DMACmd(ADC1, ENABLE); 
    /* Enable ADC1 */    
    ADC_Cmd(ADC1, ENABLE);    //使能指定的ADC1
     /* Enable ADC1 reset calibaration register */      
    ADC_ResetCalibration(ADC1);  //复位指定的ADC1的校准寄存器 
    
    /* Enable ADC1 reset calibaration register */      
    ADC_ResetCalibration(ADC1);  //复位指定的ADC1的校准寄存器 
    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);  //开始指定ADC1的校准状态 
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1)); 
    //获取指定ADC1的校准程序,设置状态则等待
		DMA_Cmd(DMA1_Channel1,ENABLE);	
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
		
}

u16 Get_ADC_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道,239个周期,提高采样时间可以提高精确度			    
	
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的ADC1的软件转换启动功能	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	}
	return temp_val/times;
} 

void DMA_Configuration(void) 
{
    /* ADC1  DMA1 Channel Config */  
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA时钟
 
    DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为缺省值：ADC1连接DMA通道1
    DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&(ADC1->DR);  //DMA外设ADC基地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_Value;      //DMA内存基地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //内存作为数据传输的目的地
    DMA_InitStructure.DMA_BufferSize =4;  //此值为完整一轮DMA传输的次数
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外设数据位宽度16位，即DMA传输尺寸
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环缓存模式，一轮结束后自动开始下轮传输
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x禁止内存到内存
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStruct中参数DMA通道
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


