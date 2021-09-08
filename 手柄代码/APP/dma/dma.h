#ifndef _DMA_H
#define _DMA_H


#include"system.h"

void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 par,u32 mar,u16 ndtr);

void DMAx_Enable(DMA_Channel_TypeDef* DMAy_Channelx,u16 ndtr);

#endif
