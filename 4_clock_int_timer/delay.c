
#include "timer.h"



/*********************************************************************************
   *Function:     delay
   *Description： 简单延时
   *Input:        循环次数
   *Output:       \
   *Return:       0
   *Others:       1500000约等于1s;
**********************************************************************************/
void  delay(unsigned int   i)
{
	volatile unsigned int count = i;
	volatile unsigned int temp = 5;
	
	for(; count > 0; count--)
		for(;temp>0;temp--);
}


/*********************************************************************************
   *Function:     delay_ms
   *Description： 精确延时,timer2
   *Input:        循环次数
   *Output:       \
   *Return:       0
   *Others:       
**********************************************************************************/
volatile unsigned int timer_delay_flag = 0;

void  delay_ms(unsigned int    i)
{
	timer_delay_flag = i;
	timer2_start();
	while(timer_delay_flag);
	timer2_stop();
	
}

