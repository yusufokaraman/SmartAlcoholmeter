#include "main.h"
uint32_t count;

void delay_us(uint32_t time)
{
     count = time;	
     while(count);
}
void delay_ms(uint32_t ms)
{
     while (ms--)
    {
        delay_us(1000);
    }
}
uint32_t millis(void)
{
  extern uint32_t time;
  return time;
}