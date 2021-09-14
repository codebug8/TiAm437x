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


int  main()
{

	uart_init();
	//led_init();
	
	_100ask_printf("uart_init ok!\r\n");
	_100ask_printf_test();

	while(1);

}
