#include "main.h"

uart_t uart6 = {UART5};
uart_t uart1 = {USART1};

FPM parmak;
FPM_System_Params parametreler;

char transmitter[50];
uint16_t yeni_parmak_ID=0,i=0;
uint16_t linenum = 0,my_finger=0;
bool match_print_bool=false,match_converted_bool=false;
extern uint16_t Selected_Button;
extern bool c_sharp_bool;

void clear_transmitter(void)
{
  uint16_t i;
  for(i=0;i<sizeof(transmitter);i++)
        transmitter[i] = 0;
}
void fingerprint_main_init(void)
{
         uart_init(&uart6);
         uart_init(&uart1);
   
        // USART_Puts(USART1,"merhaba\n\r");
          
         parmak.address=0xFFFFFFFF;
         parmak.password=0;
         parmak.manual_settings=0;
         parmak.avail_func=usart_start;
         parmak.read_func=usart_okuma;
         parmak.write_func=usart_yazma;
         
         if(fpm_begin(&parmak))
         {
           fpm_read_params(&parmak,&parametreler);
           
           delay_ms(500);
         //  USART_Puts(USART1,"parmak izi calisiyor\n\r");
		
           sprintf(transmitter,"sensor kapasitesi: %d\n\r", parametreler.capacity);  
         //  USART_Puts(USART1,transmitter);
               
           delay_ms(500);
               
           clear_transmitter();
		   delay_ms(500);
                
           sprintf(transmitter,"paket uzunlugu: %d\n\r", fpm_packet_lengths[parametreler.packet_len]);
               // USART_Puts(USART1,transmitter);
                clear_transmitter();
        delay_ms(500);
          }
         else 
         {
           sprintf(transmitter,"Did not find fingerprint sensor :( \r\n");
         //USART_Puts(USART1,transmitter);
                clear_transmitter();
		while (1);
	 }
}
void match_function(void)
{
    uint16_t IDfinger;
    uint16_t fingerscore;
    int16_t p =-1;
    USART_Puts(USART1,"Waiting for valid parmak to enroll\r\n");
    while (match_print_bool!=true) 
    {    
       p = fpm_get_image(&parmak);
    switch (p) 
        {
               case FPM_OK:
           USART_Puts(USART1,"Image taken\r\n");
           
           match_print_bool=true;
                break;
                
            case FPM_NOFINGER:
            USART_Puts(USART1,"Parmaginiz yok suan\r\n");
            delay_ms(50);
                break;
                
            default:
            sprintf(transmitter,"Error code: 0x%X!\r\n", p);
            USART_Puts(USART1,transmitter);
            clear_transmitter();
                break;
        }
    }
    // OK success!

    p = fpm_image2Tz(&parmak,1);
    while(match_converted_bool!=true)
    {
    switch (p)
    {
          case FPM_OK:
            USART_Puts(USART1,"Image converted\r\n");
            match_converted_bool=true;  
            break;
          default:
        	sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                USART_Puts(USART1,transmitter);
                clear_transmitter();
            return;
    }
    }
    p=fpm_search_database(&parmak,&IDfinger,&fingerscore,1);
    if(p==FPM_OK)
    {
      USART_Puts(USART1,"parmak izi bulundu");
      //sprintf(transmitter,"bulunan id=%d",IDfinger);
      sprintf(transmitter,"'%d",IDfinger);//parmak tanima fonksiyonu
      USART_Puts(USART1,transmitter);
      clear_transmitter();

      
        while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
                
           if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
           {
             match_converted_bool=false;
             match_print_bool=false;
           }      
      delay_ms(50);
    }   
     else 
     {
        USART_Puts(USART1,"Unknown error");
  
        while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
             
           if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
           {
             match_converted_bool=false;
             match_print_bool=false;
           }   
    }
    
}
void matchprints_mainloop(void)
{
        uint16_t temp_finger=0;
        int last_ex=5;
        last_ex=fpm_get_template_count(&parmak,&temp_finger);
        sprintf(transmitter,"last example is=%d",last_ex);
         USART_Puts(USART1,transmitter);
         clear_transmitter();
        while (1) 
        {
				//USART_Puts(USART1,"belirlenen iki deger gonderiliyor\r\n");
				while (uart_avail(&uart1) != 0);
				match_function();
				delay_ms(200);
				while (uart_read_byte(&uart1) != -1);  
                // clear buffer*
        }
}
void templates_mainloop(void)
{
	char c;
	uint8_t template_buffer[BUFF_SZ];
	while (1)
        {
		//USART_Puts(USART1,"Enter the template ID # you want to read...");
                
		uint16_t fid = 2;
		while (uart_avail(&uart1) != 0);
                my_finger=fid;
		while (1) 
                {
			while (uart_avail(&uart1) != 0);
			c = uart_read_byte(&uart1);
			if (! isdigit(c)) break;
			fid *= 10;
			fid += c - '0';
		}

		
		uint16_t total_read = read_template(fid, template_buffer, BUFF_SZ);
		if (!total_read)
			return;
	}
}
void enroll_mainloop(void) 
{
	while (1) 
        {
          
		//USART_Puts(USART1,"parmaginizi okutun lutfen\n\r");
		while (uart_avail(&uart1) != 0);
               //USART_Puts(USART1,"Searching for a free slot to store the template...\r\n");
		//USART_Puts(USART1,"parmaginizi kaydetmek icin bos sablon araniyor\r\n");
		int16_t fid;
		if (get_free_id(&fid))
                {
			enroll_finger(fid);
                       
                      //  USART_Puts(USART1,"parmak izi okundu\r\n");
                      
                }
		else
			USART_Puts(USART1,"tum alan dolu!\r\n");
		while (uart_read_byte(&uart1) != -1);  // clear buffer
	}
}
void empty_database(void)
{
  fpm_empty_database(&parmak);
  USART_Puts(USART1,"tum verileriniz silinmistir\n\r");
}
uint8_t get_free_id(int16_t * fid)
{
    int16_t p = -1;
    for (int page = 0; page < (parametreler.capacity / FPM_TEMPLATES_PER_PAGE) + 1; page++) {
        p = fpm_get_free_index(&parmak, page, fid);
        switch (p) {
            case FPM_OK:
                if (*fid != FPM_NOFREEINDEX) 
                {
                    sprintf(transmitter,"Yeni olusturulacak ID %d\n\r", *fid);
                   // USART_Puts(USART1,transmitter);
                    clear_transmitter();
                    return 1;
                }
                break;
            default:
            	printf("Error code: %d\r\n",p);
                return 0;
        }
    }
    return 0;
}
void enroll_finger(int16_t fid) 
{
    int16_t p = -1;
    //USART_Puts(USART1,"Waiting for valid parmak to enroll\n\r");
    while (p!=FPM_OK) 
    {
        p = fpm_get_image(&parmak);
        switch (p) 
        {
               case FPM_OK:
          // USART_Puts(USART1,"Image taken\n\r");
                 GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
                 delay_ms(50);
                 GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
                 delay_ms(50);
                break;
                
            case FPM_NOFINGER:
            //USART_Puts(USART1,"Parmaginiz yok suan\r\n");
            delay_ms(200);
                break;
                
            default:
            sprintf(transmitter,"Error code: 0x%X!\r\n", p);
            USART_Puts(USART1,transmitter);
            clear_transmitter();
                break;
        }
    }
    // OK success!

    p = fpm_image2Tz(&parmak, 1);
    switch (p) {
          case FPM_OK:
           // USART_Puts(USART1,"Image converted\n\r");
              break;
          default:
        	sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                USART_Puts(USART1,transmitter);
                clear_transmitter();
            return;
    }

  //  USART_Puts(USART1,"parmagi cekiniz\r\n");
    delay_ms(200);
    p = 0;
    while (p != FPM_NOFINGER) {
    	p = fpm_get_image(&parmak);
    	delay_ms(200);
    }

    p = -1;
  //  USART_Puts(USART1,"lutfen parmaginizi bir kez daha yerlestiriniz\n\r");
    
    while (p != FPM_OK) {
    	p = fpm_get_image(&parmak);
        switch (p) {
            case FPM_OK:
              //USART_Puts(USART1,"Goruntu alindi\n\r");              
              break;
              
            case FPM_NOFINGER:
               //USART_Puts(USART1,".\r\n");
                break;
            
        default:
            	sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                //USART_Puts(USART1,"hatali islem yapildi\n devam etmek icin \n butona basin");
     
                while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
                 USART_Puts(USART1,transmitter);
                 clear_transmitter();
                break;
        }
    }

    // OK success!

    p = fpm_image2Tz(&parmak, 2);
    switch (p) 
    {
        case FPM_OK:
            //USART_Puts(USART1,"Image converted\r\n");
            break;
            
        default:
        	sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                USART_Puts(USART1,"hatali islem yapildi\n devam etmek icin \n butona basin");
                 
                
                
                while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
                USART_Puts(USART1,transmitter);
                 clear_transmitter();
            return;
    }


    // OK converted!
    p = fpm_create_model(&parmak);
    switch (p) 
    {
		case FPM_OK:
			//USART_Puts(USART1,"Prints matched!\r\n");
                          GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
                 delay_ms(50);
                 GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
                 
			break;
		default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                       
                  //led veya buzzer ayarlari
         
                  while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
              
                        clear_transmitter();
			return;
    }

    char stm32_transmitter[50];
   while(Selected_Button!=9 )
    {
      if(fid<10)
    sprintf(stm32_transmitter,"        0%d\n\r",fid);
    else
      sprintf(stm32_transmitter,"          %d\n\r",fid);
    delay_ms(200);
    //sprintf(transmitter,"FingerPrint ID=%d", fid);
   // USART_SendData(USART1,fid);
    yeni_parmak_ID=fid;
      USART_Puts(USART1,stm32_transmitter);
 // USART1->DR=(uint16_t)stm32_transmitter;
    //clear_transmitter();
          if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);       
               
                      Selected_Button=USART_ReceiveData(USART1);
                       //if(Selected_Button==1)
                         p = fpm_store_model(&parmak, fid, 1);   
                        selection_function(Selected_Button); 
    }
    
    
      if(c_sharp_bool!=true)
      c_sharp_bool=true;
     while(c_sharp_bool);       
               
                      Selected_Button=USART_ReceiveData(USART1);
                      if(Selected_Button==1)
                         p = fpm_store_model(&parmak, fid, 1);   
                      selection_function(Selected_Button);   
   
   
    
    switch (p) 
    {
		case FPM_OK:
			//USART_Puts(USART1,"kaydedildi\r\n");
                       
                        delay_ms(300);
                         
                          break;
		default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return;
	}
}
uint16_t read_template(uint16_t fid, uint8_t * buffer, uint16_t buff_sz)
{
	
    int16_t p = fpm_load_model(&parmak, fid, 1);
    switch (p) 
    {
        case FPM_OK:
            sprintf(transmitter,"ornek %d yuklendi.\r\n", fid);
            USART_Puts(USART1,transmitter);
            clear_transmitter();
            
            break;
        default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return 0;
    }

    // OK success!

    p = fpm_download_model(&parmak, 1);
    switch (p) {
        case FPM_OK:
          USART_Puts(USART1,"seçilen parmak verisi bilgisayara yuklenmis durumda");
            break;
        default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                         USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return 0;
    }

    uint8_t read_finished;
    int16_t count = 0;
    uint16_t readlen = buff_sz;
    uint16_t pos = 0;

    while (1)
    {
        uint8_t ret = fpm_read_raw(&parmak, FPM_OUTPUT_TO_BUFFER, buffer + pos, &read_finished, &readlen);
        if (ret) 
        {
            count++;
            pos += readlen;
            readlen = buff_sz - pos;
            if (read_finished)
              USART_Puts(USART1,"herhangibir sikinti yok\r\n");
                break;
        }
        else 
        {
            sprintf(transmitter,"Error receiving packet %d\r\n", count);
             USART_Puts(USART1,transmitter);
             clear_transmitter();
            return 0;
        }
    }

    uint16_t total_bytes = count * fpm_packet_lengths[parametreler.packet_len];

    
    uint16_t num_rows = total_bytes / 16;

    USART_Puts(USART1,"sablon degerleri:\r\n\r\n");
    //USART_Puts(USART1,"---------------------------------------------\r\n");
    for (int row = 0; row < num_rows; row++)
    {
        for (int col = 0; col < 16; col++) 
        {
          delay_ms(100);
            sprintf(transmitter,"%d, ", buffer[row * 16 + col]);
            USART_Puts(USART1,transmitter);
            clear_transmitter();
        }
        USART_Puts(USART1,"\r\n\r\n");
    }
   //USART_Puts(USART1,"--------------------------------------------\r\n");

   sprintf(transmitter,"%d bytes read.\r\n", total_bytes);
     USART_Puts(USART1,transmitter);
            clear_transmitter();
    return total_bytes;
}
void match_prints(int16_t fid, int16_t otherfid) 
{
   
	int16_t p = fpm_load_model(&parmak, fid, 0);
	
        switch (p)
        {
		case FPM_OK:
			sprintf(transmitter,"Ornek %d yuklendi.\r\n", fid);
			USART_Puts(USART1,transmitter);
                        break;
		default:
			sprintf(transmitter,"Hatali Kod: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return;
	}

    
    p = fpm_load_model(&parmak, otherfid, 0);
    switch (p)
    {
        case FPM_OK:
            sprintf(transmitter,"ornek %d yuklendi.\r\n", otherfid);
            USART_Puts(USART1,transmitter);
            clear_transmitter();
            break;
        default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return;
    }

    uint16_t match_score = 0;
    p = fpm_match_template_pair(&parmak, &match_score);
    switch (p) 
    {
        case FPM_OK:
            sprintf(transmitter,"Match score: %d\r\n", match_score);
             USART_Puts(USART1,"parmak eslesti");
         
      while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
                 
              USART_Puts(USART1,transmitter);
            clear_transmitter();
            break;
        case FPM_NOMATCH:
            USART_Puts(USART1,"parmak taninmadi\n devam etmek icin \n lutfen butona basin");
            
 while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
                  
            USART_Puts(USART1,"Prints did not match.\r\n");
            break;
        default:
			sprintf(transmitter,"Error code: 0x%X!\r\n", p);
                        USART_Puts(USART1,transmitter);
                        clear_transmitter();
			return;
    }
}
uint16_t usart_start(void)
{
	return uart_avail(&uart6);
}
uint16_t usart_okuma(uint8_t * bytes, uint16_t len)
{
	return uart_read(&uart6, bytes, len);
}
void usart_yazma(uint8_t * bytes, uint16_t len)
{
	uart_write(&uart6, bytes, len);
}