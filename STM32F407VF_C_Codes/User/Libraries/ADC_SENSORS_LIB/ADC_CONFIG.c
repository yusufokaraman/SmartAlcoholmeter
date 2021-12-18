#include "main.h"

uint16_t counter=0,sayac=0;

//structlar
extern GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
DMA_InitTypeDef DMA_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
extern NVIC_InitTypeDef NVIC_InitStruct;

extern bool c_sharp_bool;
extern uint16_t Selected_Button;
//degiskenler

uint32_t pwm_value=0;
char string[50];
char str[50];
uint16_t adc_value[bufferlength]={0,0};
uint16_t alkol_Sensor=0,kalp_sensor=0;

void initilization(void)
{
  gpio_config();
  adc_ayar();
  dma_ayar();
  
  ADC_SoftwareStartConv(ADC1);
  
}
void gpio_config(void)
{ 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
 
 GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
 GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
 GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_1;
 GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
 GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

 GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void adc_ayar(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  
  ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
  ADC_InitStruct.ADC_ScanConvMode=ENABLE;//çoklu okumalarda bu  modu açmamiz gerekir
  ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
  ADC_InitStruct.ADC_ExternalTrigConv=0;
  ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
  ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;//tek çevrim yapilacaksa burayi disable olarak
                                               //çoklu çevrim yapilacaksa enable olarak ayarlanmali
  ADC_InitStruct.ADC_NbrOfConversion=bufferlength;//yapilacak olan çevrim sayisini gösterir
                                       //bu kisma bufferlength yazilarak da bu ayarlamayi yapabiliriz
                                      //öylece yapilacak belli sayida islemimiz olur.
  ADC_Init(ADC1,&ADC_InitStruct);
  
  ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;//tekli okumada disable edebiliriz fakat çoklu okumada bu modlari okumalarimiza göre ayarlamamiz gerekir 
  ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
  ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
  
  ADC_CommonInit(&ADC_CommonInitStruct);
  ADC_Init(ADC1,&ADC_InitStruct);
  
  ADC_Cmd(ADC1,ENABLE);
  ADC_DMACmd(ADC1,ENABLE);
  
  ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
  
  ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_4,2,ADC_SampleTime_3Cycles);
  
}
void dma_ayar(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  DMA_DeInit(DMA2_Stream0);
  
  DMA_InitStruct.DMA_Channel=DMA_Channel_0;
  DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
  DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
  DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t) & ADC1->DR;//dma ile alinacak degerlerin adresi buraya yaziliyor
  DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t) & adc_value;//Aldigin degerleri nereye yazacaksin burada onu belirliyoruz
  DMA_InitStruct.DMA_BufferSize=2;
  DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Enable;
  DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;//maks iletim miktarinin ne kadari dolunca iletim yapilsin
  DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;//dma ile perip brustlar esit olmak zorunda
  DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
  DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//veri aktarimini sürekli devam etsin diyorsak circular seçiyoruz
  DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;//memory adresini sürekli degistiginden ENABLE ediyoruz
  DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//perip adresi sürekli ayni kalacak
  
  DMA_Init(DMA2_Stream0,&DMA_InitStruct);//kullanilacak peripherali tablodan bakarak buraya ekliyoruz
  
  DMA_Cmd(DMA2_Stream0,ENABLE);
}
void Read_Alcohol(void)
{
                  alkol_Sensor=adc_value[0]/40;
                  //kalp_sensor=adc_value[1];
                  sprintf(str,"    %d\n",alkol_Sensor);
                  USART_Puts(USART1,str);
                  clear_str();
                  
                         if(c_sharp_bool!=true)
                        c_sharp_bool=true;
    
                   while(c_sharp_bool);        
               
                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);  
                 

}
void Read_Pulse_sensor(void)
{  
   
                  kalp_sensor=adc_value[1]/40;
                  sprintf(str,"    %d\n",kalp_sensor);
                  USART_Puts(USART1,str);
                  clear_str();
              
                  if(c_sharp_bool!=true)
                        c_sharp_bool=true;
    
                   while(c_sharp_bool);        
               
                      Selected_Button=USART_ReceiveData(USART1);
                      selection_function(Selected_Button);  
                 
}
 void clear_str(void)
{
  uint16_t i;
  for(i=0;i<sizeof(str);i++)
        str[i] = 0;
}            