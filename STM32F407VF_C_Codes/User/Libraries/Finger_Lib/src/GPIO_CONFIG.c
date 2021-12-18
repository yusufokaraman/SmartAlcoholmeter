#include "main.h"
GPIO_InitTypeDef GPIO_InitStruct;
void GPIO_Config(void)
{
  
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
   while (1);
 }

  //SysTick_Config(SystemCoreClock / 1000);
  //button configuration
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
  GPIO_Init(GPIOA,&GPIO_InitStruct);
  //Led pins configurations
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_7|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
  GPIO_Init(GPIOD,&GPIO_InitStruct);
 
     //HC-05 Configurations
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  
  //gpii pin degistirildi. once pb6 ve sonra pb7 idi.
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
    
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
  GPIO_Init(GPIOB,&GPIO_InitStruct);
  
    //Fingerprint module configurations
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
    
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
  GPIO_Init(GPIOC,&GPIO_InitStruct);
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
    
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
  
  GPIO_Init(GPIOD,&GPIO_InitStruct);
  
  
}


