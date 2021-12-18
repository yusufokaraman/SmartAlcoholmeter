#ifndef RFID_MAIN_FUNCTIONS_H
#define RFID_MAIN_FUNCTIONS_H
void clear_RFID(void);
void Read_RFID(void);
void Rfid_initilization(void);
uint8_t CompareID(uint8_t* CardID, uint8_t* CompareID) ;
void Read64Block(void);

#endif