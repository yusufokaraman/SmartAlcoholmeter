#include "main.h"
uint8_t CompareID(uint8_t* CardID, uint8_t* CompareID);
int control_counter=0;
void Read64Block( void);
void UARTmain_Init(void);
uint8_t status; uint8_t g_ucTempbuf[20];  bool flag_loop=0;
uint8_t defaultKeyA[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

char str[50];
char idstr[50];



void Read_RFID(void)
{
	//4 bytes = 32 bits
	uint8_t MyID[5] = {0xF7,0x6F,0xB7,0x60};
 
		MF522_init();
	
    MFRC522_Reset();
//    MFRC522_AntennaOff(); 
    MFRC522_AntennaOn();  

	while(1)
	{
          
          
          
          
		status = MFRC522_Request(PICC_REQALL, g_ucTempbuf);
    if (status != MI_OK)
    {  
		  flag_loop=0;  
      continue;
    }
		status = MFRC522_Anticoll(g_ucTempbuf);
    if (status != MI_OK)
         {  
					 flag_loop=0;  
           continue;
         }
	  if(flag_loop==1) 
        {
				 MFRC522_Halt();	
				 continue;
				}
		flag_loop=1;
		printf("\n UID=%x:%x:%x:%x\r\n",g_ucTempbuf[0],g_ucTempbuf[1],g_ucTempbuf[2],g_ucTempbuf[3] );
		MFRC522_Halt();
                sprintf(idstr,"UID=%x:%x:%x:%x\r\n",g_ucTempbuf[0],g_ucTempbuf[1],g_ucTempbuf[2],g_ucTempbuf[3] );
                USART_Puts(USART2,idstr);
	
			printf("Read 64 sector\r\n");
       Read64Block();			
	}
}
uint8_t CompareID(uint8_t* CardID, uint8_t* CompareID) 
{
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID[i] != CompareID[i]) 
			{
			return MI_ERR;
		  }
	}
	return MI_OK;
}

void Read64Block( void)
{
 uint8_t k=0,p=0;
 uint8_t  readdata[16];
 uint8_t serNum[5];
	  for(k=0;k<64;k++)			
	    {		
				 status = MFRC522_Request(PICC_REQALL, g_ucTempbuf);
         if (status != MI_OK) continue;
/*---------------------------------------------------*/				
         status = MFRC522_Anticoll(serNum);
         if (status != MI_OK) continue;
/*----------------------------------------------------*/
         status = MFRC522_Select(serNum);
         if (status != MI_OK) continue;
/*----------------------------------------------------*/
         status = MFRC522_AuthState(PICC_AUTHENT1A, k, defaultKeyA,serNum);
         if (status != MI_OK) continue;
/*----------------------------------------------------*/	
         printf("block %d\r\n", k);	
				 status = MFRC522_Read(k, readdata);
                if (status == MI_OK)
                {
									printf("hex= ");
                  for(p=0; p<16; p++)
                  {                  
									printf("%x ",readdata[p]);
                  } 
									/*
                  printf("\r\nsymbol= ");	    								
                   for(p=0; p<16; p++)
                  {                  
										printf("%c",readdata[p]);
                  } 	
									*/
                  printf("\r\n\r\n");									        
                  MFRC522_Halt();
              }
       }
}

