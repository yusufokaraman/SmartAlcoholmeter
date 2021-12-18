#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include "main.h"

#define UART_MAX_TX_SIZE       256
#define UART_MAX_RX_SIZE       256

#define USART_TIMEOUT 500
#define HEX_CHARS          "0123456789ABCDEF"

void USART_Config(void);
void USART_Puts(USART_TypeDef* USARTx,volatile char *s);
void Finger_write(USART_TypeDef* USARTx,unsigned char data);
void nvic_config(void);
void clear_buf(uint16_t *buffer);
void UART_SendHex16(USART_TypeDef* USARTx, uint16_t num);

#endif

