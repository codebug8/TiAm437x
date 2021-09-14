/*************************************************************************
    > File Name: led.c
    > Author: hceng
    > Description: 完善AM437X裸机LED
    > Created Time: 20170726
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"

//针对哪个板子，就只打开哪个宏；
#define TI_BOARD   0
//#define MYIR_BOARD 0

#ifdef  TI_BOARD

/****************************************************************************
                                 TI_BOARD_KEY
---------------------------------------------------------------------------
Key                                       Pin
---------------------------------------------------------------------------
SW6     PLAT_MTST5(E24:gpio5_13)         -PLAT_STST1(R24:spi4_d0/gpio5_5)      
SW7     PLAT_MTST5(E24:gpio5_13)         -PLAT_STST2(P24:spi4_d1/gpio5_6)
SW8     PLAT_STST1(P25:spi4_sclk/gpio5_4)-PLAT_STST1(R24:spi4_d0/gpio5_5)
SW9     PLAT_STST1(P25:spi4_sclk/gpio5_4)-PLAT_STST2(P24:spi4_d1/gpio5_6)
---------------------------------------------------------------------------
mode1: gpio5_13 high,gpio5_4 low,check gpio5_5 and gpio5_6.
mode2: gpio5_13 low,gpio5_4 high,check gpio5_5 and gpio5_6.
*****************************************************************************/


void key_init(void)
{
	//1.使能GPIO外设时钟. CP468
	PRCM_CM_PER_GPIO5_CLKCTRL  = (0x01<<1);//CP511

	//2.设置4个GPIO模式;CP642
	CTRL_CONF_GPIO5_13   &= ~(0x01<<18);//关闭输入
	CTRL_CONF_GPIO5_13   |=  (0x01<<17);//设置上拉
	CTRL_CONF_SPI4_SCLK  &= ~(0x01<<18);//关闭输入
	CTRL_CONF_SPI4_SCLK  |=  (0x01<<17);//设置上拉	
	CTRL_CONF_SPI4_D0   |=  (0x01<<16);//关闭上下拉
	CTRL_CONF_SPI4_D1	|=	(0x01<<16);//关闭上下拉

	//3.设置输入/输出;CP3731
	GPIO5->OE &= ~(0x01<<4 | 0x01<<13);//设置输出
	GPIO5->OE |=  (0x01<<5 | 0x01<<6); //设置输入

	//4.设置允许输出位;
	GPIO5->SETDATAOUT |= (0x01<<4 | 0x01<<13);

}


unsigned char get_key_val(void)
{	
	unsigned int key_val = 0;
	
	GPIO5->DATAOUT &= ~(0x01<<4);
	GPIO5->DATAOUT |=  (0x01<<13);
	if((GPIO5->DATAIN & (0x01<<5)) ? 1 : 0)
	{
		delay(10000);
		if((GPIO5->DATAIN & (0x01<<5)) ? 1 : 0)
			key_val = 1;
	}
		
	if((GPIO5->DATAIN & (0x01<<6)) ? 1 : 0)
	{
		delay(10000);
		if((GPIO5->DATAIN & (0x01<<6)) ? 1 : 0)
			key_val = 2;
	}

	GPIO5->DATAOUT &= ~(0x01<<13);
	GPIO5->DATAOUT |=  (0x01<<4);
	if((GPIO5->DATAIN & (0x01<<5)) ? 1 : 0)
	{
		delay(10000);
		if((GPIO5->DATAIN & (0x01<<5)) ? 1 : 0)
			key_val = 3;
	}	
	if((GPIO5->DATAIN & (0x01<<6)) ? 1 : 0)
	{
		delay(10000);
		if((GPIO5->DATAIN & (0x01<<6)) ? 1 : 0)
			key_val = 4;
	}
	
	return key_val;
}


#endif



#ifdef  MYIR_BOARD
void  led_on(void)
{
	//am437x手册140的CM_PER，468页、507页
	PRCM_CM_PER_GPIO1_CLKCTRL  = (2);
	//等待bit[17-16]=0,
	//简单起见，先延时
	delay(5000);

	CTRL_CONF_GPMC_A8  = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A9  = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A10 = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A11 = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);	

	//GPIO1_OE = (0xFEFFFFFF);//bit24=1
	GPIO1_SETDATAOUT = (0xFFFFFFFF);
    GPIO1_OE &=~((1<<27) | (1<<26)  | (1<<25)  | (1<<24));
	
	//while(1)
	{
		//
		//GPIO1_CLRDATAOUT = (0x01000000);
		GPIO1_CLRDATAOUT = (1<<24);//gpio1_24
		delay(500000);
		//while(1);
		//GPIO1_SETDATAOUT = (0x01000000);
		GPIO1_SETDATAOUT = (1<<24);//gpio1_24
		delay(500000);

		GPIO1_CLRDATAOUT = (1<<25);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<25);//gpio1_24
		delay(500000);	

		GPIO1_CLRDATAOUT = (1<<26);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<26);//gpio1_24
		delay(500000);	

		GPIO1_CLRDATAOUT = (1<<27);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<27);//gpio1_24
		delay(500000);			
	}

}

void  led_off()
{
	GPIO1_SETDATAOUT |=  (1<<24);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<25);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<26);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<27);//gpio1_24
}

void led1_on()
{
	GPIO1_CLRDATAOUT |=  (1<<24);//gpio1_24
}

void led1_off()
{
	GPIO1_SETDATAOUT |=  (1<<24);//gpio1_24
}

void led2_on()
{
	GPIO1_CLRDATAOUT |=  (1<<25);//gpio1_24
}

void led2_off()
{
	GPIO1_SETDATAOUT |=  (1<<25);//gpio1_24
}

void led3_on()
{
	GPIO1_CLRDATAOUT |= (1<<26);//gpio1_24
}

void led3_off()
{
	GPIO1_SETDATAOUT |= (1<<26);//gpio1_24
}

void led4_on()
{
	GPIO1_CLRDATAOUT |=  (1<<27);//gpio1_24
}

void led4_off()
{
	GPIO1_SETDATAOUT |=  (1<<27);//gpio1_24
}
#endif
	
