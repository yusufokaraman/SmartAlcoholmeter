#include "main.h"

uint8_t CompareID(uint8_t* CardID, uint8_t* CompareID);
int control_counter=0;
void Read64Block( void);
void UARTmain_Init(void);
uint8_t status; uint8_t g_ucTempbuf[20],rfid_temp;  bool flag_loop=0;
uint8_t defaultKeyA[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
extern int rfid_counter;
char idstr[50];
extern bool c_sharp_bool;
extern uint16_t Selected_Button;

void clear_RFID(void)
{
  uint16_t i;
  for(i=0;i<sizeof(idstr);i++)
        idstr[i] = 0;
}

void Read_RFID(void)
{
	

	while(1)
	{
          rfid_counter++;
          
          
          
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
		//printf("\n UID=%x:%x:%x:%x\r\n",g_ucTempbuf[0],g_ucTempbuf[1],g_ucTempbuf[2],g_ucTempbuf[3] );
		MFRC522_Halt();
                //rfid_temp=g_ucTempbuf[0]<<12|g_ucTempbuf[1]<<8|g_ucTempbuf[2]<<8|g_ucTempbuf[3]<<8;
                sprintf(idstr,"               %x:%x:%x:%x\r\n",g_ucTempbuf[0],g_ucTempbuf[1],g_ucTempbuf[2],g_ucTempbuf[3] );

                 
                 USART_Puts(USART1,idstr);
                 
                
                      
                       
   if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);   
                 
                
                //clear_RFID();
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
void Rfid_initilization(void)
{		
    MF522_init();
    MFRC522_Reset();
    MFRC522_AntennaOn();  
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

