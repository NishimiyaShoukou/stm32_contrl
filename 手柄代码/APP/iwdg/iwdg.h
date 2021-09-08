#ifndef _IWDG_H
#define _IWDG_H

#include"system.h"

void IWDG_Init(u8 pre,u16 rlr);

void IWDG_FeedDog(void);

#endif
