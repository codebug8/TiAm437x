/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: AM437X裸机i2c
    > Created Time: 20170815
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "printf.h"
#include "key.h"
#include "clkout.h"
#include "int.h"
#include "timer.h"
#include "i2c.h"



int  main()
{
    unsigned int i;
	

	uart_init();
	//led_init();
	gic_init();
	timer2_init();
	i2c_init();
	printf("uart_init ok.\n\r");



	eeprom_write(0,0);
	delay_ms(10);

	eeprom_write(1,2);
	delay_ms(10);

	eeprom_write(2,4);
	delay_ms(10);

	eeprom_write(3,6);
	delay_ms(10);

	eeprom_write(4,8);
	delay_ms(10);

	eeprom_write(5,10);

	delay_ms(100);

	
	//printf("read_data = %d\n\r", eeprom_read(1));

	for(i=0; i<5; i++)
	{
		printf("read_data%d = %d\n\r",i, eeprom_read(i));
		delay_ms(10);
	}


	while(1)
	{

	}

	return 0;
}




