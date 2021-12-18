#include "main.h"

 USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void USART_Config(void)
{
  //hc-05 usart configurations
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  
  USART_InitStruct.USART_BaudRate=9600;
  USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  
  USART_Init(USART1,&USART_InitStruct);
  
  USART_Cmd(USART1,ENABLE);
  
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  
  //fingerprint module usart configurations
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
 
  USART_InitStruct.USART_BaudRate=57600;
  USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  
  USART_Init(UART5,&USART_InitStruct);
  
  USART_Cmd(UART5,ENABLE);
   
  USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
  
}
void nvic_config()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
   
  NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
  
  NVIC_Init(&NVIC_InitStruct);
        
  NVIC_InitStruct.NVIC_IRQChannel=UART5_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
  
  NVIC_Init(&NVIC_InitStruct);
}

void USART_Puts(USART_TypeDef* USARTx,volatile char *s)
{
   while(*s)
  {
    while(!(USARTx->SR&0x00000040));
    USART_SendData(USARTx,*s);
    *s++;
  }
}

void UART_SendChar(USART_TypeDef* USARTx, char ch)
{
	USARTx->DR = ch;
	while (!(USARTx->SR & USART_SR_TC)); // wait for "Transmission Complete" flag cleared
}

// Send byte in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - 8-bit value to send
void UART_SendHex8(USART_TypeDef* USARTx, uint8_t num) {
	UART_SendChar(USARTx,HEX_CHARS[(num >> 4)   % 0x10]);
	UART_SendChar(USARTx,HEX_CHARS[(num & 0x0f) % 0x10]);
}

// Send 16-bit value in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - 16-bit value to send
void UART_SendHex16(USART_TypeDef* USARTx, uint16_t num) {
	uint8_t i;
	for (i = 12; i > 0; i -= 4)
          UART_SendChar(USARTx,HEX_CHARS[(num >> i) % 0x10]);
        
	UART_SendChar(USARTx,HEX_CHARS[(num & 0x0f) % 0x10]);
}

// Send 32-bit value in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - 32-bit value to send
void UART_SendHex32(USART_TypeDef* USARTx, uint32_t num) {
	uint8_t i;
	for (i = 28; i > 0; i -= 4)	
          UART_SendChar(USARTx,HEX_CHARS[(num >> i) % 0x10]);
        
	UART_SendChar(USARTx,HEX_CHARS[(num & 0x0f) % 0x10]);
}

// Send zero terminated string to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   str - pointer to zero terminated string
void UART_SendStr(USART_TypeDef* USARTx, char *str) 
{
	while (*str) 
        {
           while(!(USARTx->SR&0x00000040));
           UART_SendChar(USARTx,*str++);
        }
}

// Send buffer to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   buf - pointer to the buffer
//   bufsize - size of buffer in bytes
void UART_SendBuf(USART_TypeDef* USARTx, char *buf, uint16_t bufsize) 
{
	while (bufsize--) 
          UART_SendChar(USARTx,*buf++);
}

void UART_SendBufHex(USART_TypeDef* USARTx, char *buf, uint16_t bufsize) 
{
	char ch;

	while (bufsize--) 
        {
		ch = *buf++;
		UART_SendChar(USARTx,HEX_CHARS[(ch >> 4)   % 0x10]);
		UART_SendChar(USARTx,HEX_CHARS[(ch & 0x0f) % 0x10]);
	}
}