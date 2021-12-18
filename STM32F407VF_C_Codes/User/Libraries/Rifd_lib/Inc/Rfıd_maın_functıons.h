#ifndef RFID_MAIN_FUNCTIONS_H
#define RFID_MAIN_FUNCTIONS_H

void delay_ms(uint32_t time);
uint32_t millis(void);
void Read_RFID(void);
uint8_t CompareID(uint8_t* CardID, uint8_t* CompareID) ;
void Read64Block( void);

#endif