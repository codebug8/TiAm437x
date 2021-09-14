/*************************************************************************
    > File Name: led.c
    > Author: hceng
    > Description: 完善AM437X裸机LED
    > Created Time: 20170726
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"



void led_init(void)
{
	//1.使能GPIO外设时钟. CP468
	PRCM_CM_PER_GPIO5_CLKCTRL  = (0x01<<1);//CP511

	//2.设置4个GPIO模式、使能上/下拉、关闭输入、设置上拉;CP642
	CTRL_CONF_GPIO5_8  &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_GPIO5_8  |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_GPIO5_9  &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_GPIO5_9  |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_GPIO5_10 &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_GPIO5_10 |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_GPIO5_11 &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_GPIO5_11 |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉


	//3.设置为输出;CP3731
	GPIO5->OE &= ~(0x01<<8 | 0x01<<9 | 0x01<<10 | 0x01<<11);

	//4.设置允许输出位;
	GPIO5->SETDATAOUT |= (0x01<<8 | 0x01<<9 | 0x01<<10 | 0x01<<11);
	
	delay(1000);
	GPIO5->DATAOUT |= (0x01<<8 | 0x01<<9 | 0x01<<10 | 0x01<<11);
	delay(1000);
	GPIO5->DATAOUT &= ~(0x01<<8 | 0x01<<9 | 0x01<<10 | 0x01<<11);
	
	//GPIO5_OE = (0xFEFFFFFF);//bit24=1
	GPIO5->SETDATAOUT = (0xFFFFFFFF);
    GPIO5->OE &=~((1<<11) | (1<<10)  | (1<<9)  | (1<<8));
#if 0	
	while(1)
	{
		//
		//GPIO5_CLRDATAOUT = (0x01000000);
		GPIO5->CLRDATAOUT = (1<<8);//GPIO5_8
		delay(500000);
		//while(1);
		//GPIO5_SETDATAOUT = (0x01000000);
		GPIO5->SETDATAOUT = (1<<8);//GPIO5_9
		delay(500000);

		GPIO5->CLRDATAOUT = (1<<9);//GPIO5_10
		delay(500000);
		GPIO5->SETDATAOUT = (1<<9);//GPIO5_11
		delay(500000);	

		GPIO5->CLRDATAOUT = (1<<10);//GPIO5_24
		delay(500000);
		GPIO5->SETDATAOUT = (1<<10);//GPIO5_24
		delay(500000);	

		GPIO5->CLRDATAOUT = (1<<11);//GPIO5_24
		delay(500000);
		GPIO5->SETDATAOUT = (1<<11);//GPIO5_24
		delay(500000);			
	}

#endif
}
