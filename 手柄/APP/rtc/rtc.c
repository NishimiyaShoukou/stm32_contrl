#include"rtc.h"


_calendar calendar;

void RTC_NVIC_Config()
{
		NVIC_InitTypeDef NVIC_InitStruct;
	
		NVIC_InitStruct.NVIC_IRQChannel=RTC_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	
	
}
void  RTC_Get()
{
		u32 timmedata=0;
		u32 temecount=0;
		
		timmedata=RTC_GetCounter();
		temecount=timmedata%86400;
		calendar.hour=temecount/3600;
		calendar.min=(temecount%3600)/60;
		calendar.sec=temecount%60;
}
//返回1，初始化失败
//返回0，成功
u8 RTC_Init()
{
	  u8 temp=0;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);//打开后备寄存器访问
	
		if(BKP_ReadBackupRegister(BKP_DR1)!=0xA0A0)
		{
				BKP_DeInit();
				RCC_LSEConfig(RCC_LSE_ON);
				while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET&&temp<255)
				{
					temp++;
					delay_ms(10);
				}
				if(temp>=250)
				return 1;
				
				RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
				RCC_RTCCLKCmd(ENABLE);
				RTC_WaitForLastTask();
				RTC_WaitForSynchro();
				RTC_ITConfig(RTC_IT_SEC,ENABLE);
				RTC_EnterConfigMode();
				RTC_SetPrescaler(32767);
				RTC_WaitForLastTask();
				RTC_SetCounter(0xD5C0);  //
				RTC_ExitConfigMode();
				
				BKP_WriteBackupRegister(BKP_DR1,0xA0A0);
		}
		else 
		{
				RTC_WaitForLastTask();
				RTC_WaitForSynchro();
				RTC_ITConfig(RTC_IT_SEC,ENABLE);
		}
		RTC_Get();
		RTC_NVIC_Config();
		return 0;
	
}

void RTC_IRQHandler(void)
{
		if(RTC_GetITStatus(RTC_IT_SEC)!=RESET)
		{
				RTC_Get();
				printf("RTC Time:%d:%d:%d\r\n",calendar.hour,calendar.min,calendar.sec);
		}
		RTC_ClearITPendingBit(RTC_IT_SEC);
}


