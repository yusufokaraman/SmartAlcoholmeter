#ifndef __MAIN_H
#define __MAIN_H

    

#define bufferlength 2

/* Includes*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADC_CONFIG.h"
#include "stdbool.h"
#include "string.h"
#include "mfrc522.h"
#include "Rfid_main_functions.h"
#include "GPIO_CONFIG.h"
#include "USART_CONFIG.h" 
#include "delay.h"
#include "FINGER_MAIN_FUNCTIONS.h"
#include "Finger_print .h"
#include "UART_Function.h"
#include <stdio.h>
#include <ctype.h>

void selection_function(uint16_t selectnum);
void Buzzer(void);
void low_Value(void);
void veritabani(void);
void Two_high(void);
void kirmizi_buzzer(void);

#endif 
