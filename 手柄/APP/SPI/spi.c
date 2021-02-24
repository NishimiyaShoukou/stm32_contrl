#include "spi.h"


void SPI_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

    //CS
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=SPI_CS_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(SPI_CS_PORT, &GPIO_InitStruct);
    //SCK
    GPIO_InitStruct.GPIO_Pin=SPI_SCK_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(SPI_SCK_PORT,&GPIO_InitStruct);
    //MISO
    GPIO_InitStruct.GPIO_Pin=SPI_MISO_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_MISO_PORT,&GPIO_InitStruct);
    //MOSI
    GPIO_InitStruct.GPIO_Pin=SPI_MOSI_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(SPI_MOSI_PORT,&GPIO_InitStruct);  

    SPI_CS_HIGH;
    SPI_SCK_LOW;
}


u8 SPI_RW(u8 data)
{
    u8 i;
    SPI_SCK_LOW;     //先将时钟线拉低
    for(i=0;i<8;i++)
    {   
        if((data&0x80)==0x80)  //从高位发送
        {
            SPI_MOSI_HIGH;
        }
        else
        {
            SPI_MOSI_LOW;
        }

        SPI_SCK_HIGH;  //将时钟线拉高，在时钟上升沿，数据发送到从设备

        data<<=1;

        if(SPI_MISO_READ)   //读取从设备发射的数据
        {
            data|=0x01;     
        }
        SPI_SCK_LOW;     //在下降沿数据被读取到主机
    }

    return data;         //返回读取到的数据
}

u8 SPI_Moni_Write_Reg(u8 Reg,u8 data)
{
  u8 states;
	SPI_CS_LOW;  //先将CSN拉低

	states=SPI_RW(Reg);  //写入寄存器的地址,即图中的Cn位，并读取状态位

	SPI_RW(data);       // 要写入的数据

	SPI_CS_HIGH;

	return states;   

}
//读寄存器操作：
u8 SPI_Moni_Read_Reg(u8 Reg)
{
    u8 data;

    SPI_CS_LOW;

    SPI_RW(Reg);   //先写入寄存器的地址

    data=SPI_RW(0); //通过写入无效数据0，将从设备上的数据挤出来

    SPI_CS_HIGH;

    return data;
}

u8 SPI_Moni_Write_Buf(u8 Reg,u8 *Buf,u8 len)
{
    u8 states;

    SPI_CS_LOW;

    states=SPI_RW(Reg);

    while(len>0)
    {
        SPI_RW(*Buf);
        Buf++;
        len--;
    }
    SPI_CS_HIGH;

    return states;
}

u8 SPI_Moni_Read_Buf(u8 Reg,u8 *Buf,u8 len)
{
    u8 states;

    SPI_CS_LOW;

    states=SPI_RW(Reg);

    while(len>0)
    {
        *Buf=SPI_RW(0);
        Buf++;
        len--;
    }

    SPI_CS_HIGH;

    return states;
}

