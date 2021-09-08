#include"dma.h"

void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 par,u32 mar,u16 ndtr)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
		DMA_InitStructure.DMA_PeripheralBaseAddr=par;
		DMA_InitStructure.DMA_MemoryBaseAddr=mar;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize=ndtr;
		DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;
		DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	
		DMA_Init(DMAy_Channelx, &DMA_InitStructure);
		
		
			
}

void DMAx_Enable(DMA_Channel_TypeDef* DMAy_Channelx,u16 ndtr)
{
		DMA_Cmd(DMAy_Channelx,DISABLE);
		DMA_SetCurrDataCounter(DMAy_Channelx,ndtr);
		DMA_Cmd(DMAy_Channelx,ENABLE);
	
	
}
