/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: AM437X裸机clkout
    > Created Time: 20170811
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"
#include "uart.h"
#include "printf.h"
#include "key.h"

int  main()
{
	unsigned char val;

	uart_init();
//	led_init();
	key_init();
//	_100ask_printf("uart_init ok!\r\n");
	


	while(1);
	 val = get_key_val();
	 _100ask_printf("init key_val  %d!\r\n", val);

	
}
