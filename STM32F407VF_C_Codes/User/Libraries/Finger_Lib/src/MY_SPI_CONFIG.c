#include "main.h"
extern SPI_InitTypeDef SPI_InitStruct;
extern GPIO_InitTypeDef GPIO_InitStruct;
void SPI_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
  
	SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_CPHA=SPI_CPHA_2Edge;//kaç edgede clock aktif olacak onu ayarlar
	SPI_InitStruct.SPI_CPOL=SPI_CPOL_High;
	SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_LSB;
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS=SPI_NSS_Soft|SPI_NSSInternalSoft_Set;
	
	SPI_Init(SPI3,&SPI_InitStruct);
	
	SPI_Cmd(SPI1,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
     	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
   	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
   	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
   	GPIO_Init(GPIOE,&GPIO_InitStruct);
}