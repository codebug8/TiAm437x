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
#include "clkout.h"
#include "int.h"
#include "timer.h"

int  main()
{
	
	clkout_init();
	uart_init();
	gic_init();
	timer2_init();
	
	
	printf("init ok.\n\r");


	
	return 0;
}




