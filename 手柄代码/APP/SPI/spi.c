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
    SPI_SCK_LOW;     //�Ƚ�ʱ��������
    for(i=0;i<8;i++)
    {   
        if((data&0x80)==0x80)  //�Ӹ�λ����
        {
            SPI_MOSI_HIGH;
        }
        else
        {
            SPI_MOSI_LOW;
        }

        SPI_SCK_HIGH;  //��ʱ�������ߣ���ʱ�������أ����ݷ��͵����豸

        data<<=1;

        if(SPI_MISO_READ)   //��ȡ���豸���������
        {
            data|=0x01;     
        }
        SPI_SCK_LOW;     //���½������ݱ���ȡ������
    }

    return data;         //���ض�ȡ��������
}

u8 SPI_Moni_Write_Reg(u8 Reg,u8 data)
{
  u8 states;
	SPI_CS_LOW;  //�Ƚ�CSN����

	states=SPI_RW(Reg);  //д��Ĵ����ĵ�ַ,��ͼ�е�Cnλ������ȡ״̬λ

	SPI_RW(data);       // Ҫд�������

	SPI_CS_HIGH;

	return states;   

}
//���Ĵ���������
u8 SPI_Moni_Read_Reg(u8 Reg)
{
    u8 data;

    SPI_CS_LOW;

    SPI_RW(Reg);   //��д��Ĵ����ĵ�ַ

    data=SPI_RW(0); //ͨ��д����Ч����0�������豸�ϵ����ݼ�����

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

