#include "main.h"

uint16_t Selected_Button=0;
bool c_sharp_bool=true;
int rfid_counter=0;
int main()
{
 	 GPIO_Config();  
         nvic_config();
         USART_Config();
         Rfid_initilization();
         initilization();
         
          
          while(c_sharp_bool);

         c_sharp_bool=true;
        
         Selected_Button=USART_ReceiveData(USART1);
         delay_ms(500);
         selection_function(Selected_Button);  
        
         while(1)
         {
           delay_ms(100);
 if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);   
       
            
         }
}
void selection_function(uint16_t selectnum)
{
    
  if(selectnum==1)  
  {
     fingerprint_main_init();
    enroll_mainloop();    
  }
  if(selectnum==2)
          Read_RFID();
      
  if(selectnum==3)
  {
       Read_Alcohol();
  }
  if(selectnum==4)
      Read_Pulse_sensor();
  
  if(selectnum==5)
          Buzzer();  
  
  if(selectnum==8)
          low_Value();

  if(selectnum==6)
         veritabani();
  
  if(selectnum==7)
           Two_high();

   if(selectnum==10)
         kirmizi_buzzer();
}
void Buzzer(void)
{
  
  GPIO_SetBits(GPIOD,GPIO_Pin_7);
  delay_ms(500);
  GPIO_ResetBits(GPIOD,GPIO_Pin_7);
  delay_ms(500);
  
  if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);   
}
void low_Value(void)
{
  GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_7);
  delay_ms(200);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_7);
  delay_ms(200);
  
  if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);   
}
void veritabani(void)
{
  
  GPIO_SetBits(GPIOD,GPIO_Pin_12);
  delay_ms(200);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12);
  //delay_ms(200);
  
   if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                     /* if(Selected_Button!=1)
                         p = fpm_store_model(&parmak, fid, 1);   */
                      selection_function(Selected_Button);   
}
void Two_high(void)
{
  GPIO_SetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  GPIO_ResetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  GPIO_SetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  GPIO_ResetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  GPIO_SetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  GPIO_ResetBits(GPIOD,GPIO_Pin_7);
  delay_ms(400);
  
  if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                     /* if(Selected_Button!=1)
                         p = fpm_store_model(&parmak, fid, 1);   */
                      selection_function(Selected_Button);   
}
void kirmizi_buzzer(void)
{
   
  GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_7);
  delay_ms(1000);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_7);
  delay_ms(100);

  if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);        

                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);   
}
