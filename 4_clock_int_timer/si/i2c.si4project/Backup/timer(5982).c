#include "AM437X/AM437X_SOC.h"
#include "timer.h"
#include "uart.h"
#include "printf.h"
#include "led.h"
#include "int.h"  

//1 选择定时器的时钟源
//2 定时器复位
//3 关闭定时器
//4 时钟预分频
//5 计数值，从而计算到单次计时时间
//6 单次定时还是多次循环定时，多次重装。
//7 软件查询还是中断服务函数来实现，是否需要定时器中断。
//8 打开定时器，从而定时器开始工作


static void  timer2_wait_complete(void)
{
	unsigned int temp1=0,temp2=0;

	temp1 = DMTIMER2->TSICR;

	if( temp1 & (0x01<<2) )
	{
		do
		{
			temp2 = DMTIMER2->TWPS;
		}
		while(0!=temp2);//等待TWPS的所有bit全部为0
	}

}


static void timer2_clock_enable(void)
{
	/*1.timer clock source and enable.*/
	PRCM_CM_DPLL_CLKSEL_TIMER2_CLK &= ~(0x03<<0);
	PRCM_CM_DPLL_CLKSEL_TIMER2_CLK |=  (0x01<<0);//1:Select CLK_M_OSC clock.2:Select CLK_32KHZ clock CP444

	PRCM_CM_PER_TIMER2_CLKCTRL |= (0x02<<0);//Module is explicitly enabled.CP525
	
    while( !( PRCM_CM_PER_L4LS_CLKSTCTRL & ((1<<12) | (1<<8))));//CP496
}


static void timer2_config(void)
{
	//1.reset timer. CP2768
	DMTIMER2->TIOCP_CFG |= (0x01<<0);//Read 1 : initiate software reset Write 1 : Reset ongoing
	while(DMTIMER2->TIOCP_CFG & (0x01<<0));	

	//2.Stop timer.
	timer2_wait_complete();
	DMTIMER2->TCLR &= ~(0x01<<0);

	//3. set timer.
	//3.1 Pre-scale clock and enable.
	timer2_wait_complete();
	DMTIMER2->TCLR &= ~(0x07<<2);
	timer2_wait_complete();
	//DMTIMER2->TCLR |= ( (0x01<<5) | (0x06<<2));//PRE=1,PTV=6
	//DMTIMER2->TCLR &= ~(0x01<<5);
	DMTIMER2->TCLR |= ( (0x01<<5) | (0x01<<2));//PRE=1,PTV=1,PS=4

#if 1
	//3.2 timer mode. overflow mode.
	timer2_wait_complete();
	DMTIMER2->TCLR &= ~(0x01<<6);
	//3.3 Auto-reload mode
	timer2_wait_complete();
	DMTIMER2->TCLR |=  (0x01<<1);
	
	//4. set load vale.
	timer2_wait_complete();
	DMTIMER2->TLDR = 0xFFFFE890;
	DMTIMER2->TCRR = 0xFFFFE890;
#endif

#if 0
	//3.2 timer mode. Capture mode.
	timer2_wait_complete();
	//DMTIMER2->TCLR |=  (0x01<<6);
	DMTIMER2->TCLR &=  ~(0x01<<6);
	//3.3 Auto-reload mode
	timer2_wait_complete();
	DMTIMER2->TCLR |=  (0x01<<1);

	//4. set load vale.
	timer2_wait_complete();
	DMTIMER2->TLDR = 0;//load_value
	timer2_wait_complete();
	//DMTIMER2->TMAR = 0x7D00;
	DMTIMER2->TLDR = 0xFFFD2393; //(0xffffffff - 187500);
	DMTIMER2->TCRR = 0xFFFD2393; //(0xffffffff - 187500);
#endif

	timer2_wait_complete();//DMTimerWaitForWrite(0x1<<1);

}

void timer2_start(void)
{
	//4. set load vale.
	timer2_wait_complete();
	DMTIMER2->TLDR = 0xFFFFE890;
	DMTIMER2->TCRR = 0xFFFFE890;

	DMTIMER2->TCLR |=  (0x01<<0);
}

void timer2_stop(void)
{
	DMTIMER2->TCLR &= ~(0x01<<0);
}

static void timer2_int_enalbe(void)
{
	DMTIMER2->IRQEN_SET |= (0x01<<1); /* IRQ enable for Overflow */
}

static void timer2_int_clear(void)
{
	DMTIMER2->IRQSTS |= (0x07<<0);
}

void  timer2_init(void)
{
	timer2_clock_enable();

	timer2_config();

	register_irq(IRQ_TIMER2, timer2_irq);

	interrupt_init(IRQ_TIMER2);

	timer2_int_enalbe();
}

void timer2_irq(void)
{
	if(timer_delay_flag > 0)
		timer_delay_flag--;
	/*
	if(DMTIMER2->IRQSTS	& (0x01<<0))
	{
		uart_PutString("int Match");
	}
	else if(DMTIMER2->IRQSTS  & (0x01<<1)) 
	{
		uart_PutString("int overflow");
	}
	else
	{
		uart_PutString("int unknown");
	}
	*/
	
	timer2_int_clear();
}


void debug_timer2(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
	_100ask_printf("PRCM_CM_DPLL_CLKSEL_TIMER2_CLK= 0x%x\r\n",PRCM_CM_DPLL_CLKSEL_TIMER2_CLK);  
	_100ask_printf("PRCM_CM_PER_TIMER2_CLKCTRL    = 0x%x\r\n",PRCM_CM_PER_TIMER2_CLKCTRL    );  
	_100ask_printf("PRCM_CM_PER_L4LS_CLKSTCTRL    = 0x%x\r\n",PRCM_CM_PER_L4LS_CLKSTCTRL    ); 
	
	_100ask_printf("DMTIMER2->TIDR      = 0x%x\r\n", DMTIMER2->TIDR      );  
	_100ask_printf("DMTIMER2->TIOCP_CFG = 0x%x\r\n", DMTIMER2->TIOCP_CFG ); 
	_100ask_printf("DMTIMER2->IRQ_EOI   = 0x%x\r\n", DMTIMER2->IRQ_EOI   );  
	_100ask_printf("DMTIMER2->IRQSTS_RAW= 0x%x\r\n", DMTIMER2->IRQSTS_RAW); 
	_100ask_printf("DMTIMER2->IRQSTS    = 0x%x\r\n", DMTIMER2->IRQSTS    );  
	_100ask_printf("DMTIMER2->IRQEN_SET = 0x%x\r\n", DMTIMER2->IRQEN_SET ); 
	_100ask_printf("DMTIMER2->IRQEN_CLR = 0x%x\r\n", DMTIMER2->IRQEN_CLR );  
	_100ask_printf("DMTIMER2->IRQWAKEEN = 0x%x\r\n", DMTIMER2->IRQWAKEEN ); 
	_100ask_printf("DMTIMER2->TCLR      = 0x%x\r\n", DMTIMER2->TCLR      );  
	_100ask_printf("DMTIMER2->TCRR      = 0x%x\r\n", DMTIMER2->TCRR      ); 
	_100ask_printf("DMTIMER2->TLDR      = 0x%x\r\n", DMTIMER2->TLDR      );  
	_100ask_printf("DMTIMER2->TTGR      = 0x%x\r\n", DMTIMER2->TTGR      ); 
	_100ask_printf("DMTIMER2->TWPS      = 0x%x\r\n", DMTIMER2->TWPS      );  
	_100ask_printf("DMTIMER2->TMAR      = 0x%x\r\n", DMTIMER2->TMAR      ); 
	_100ask_printf("DMTIMER2->TCAR1     = 0x%x\r\n", DMTIMER2->TCAR1     );  
	_100ask_printf("DMTIMER2->TSICR     = 0x%x\r\n", DMTIMER2->TSICR     ); 
	_100ask_printf("DMTIMER2->TCAR2     = 0x%x\r\n", DMTIMER2->TCAR2     );  
	_100ask_printf("******************************************************\r\n");
}



//----------------------------------------------------------------------------------------------------------//
//for PWM.


static void  timer4_wait_complete(void)
{
	unsigned int temp1=0,temp2=0;

	temp1 = DMTIMER4->TSICR;

	if( temp1 & (0x01<<2) )
	{
		do
		{
			temp2 = DMTIMER4->TWPS;
		}
		while(0!=temp2);//等待TWPS的所有bit全部为0
	}

}

static void timer4_clock_enable(void)
{
	/*1.timer clock source and enable.*/
	PRCM_CM_DPLL_CLKSEL_TIMER4_CLK &= ~(0x03<<0);
	PRCM_CM_DPLL_CLKSEL_TIMER4_CLK |=  (0x01<<0);//1:Select CLK_M_OSC clock.2:Select CLK_32KHZ clock CP444

	PRCM_CM_PER_TIMER4_CLKCTRL |= (0x02<<0);//Module is explicitly enabled.CP525
	
    while( !( PRCM_CM_PER_L4LS_CLKSTCTRL & ((1<<14) | (1<<8))));//CP496
}

static void timer4_config(void)
{
	//1.reset timer. CP2768
	DMTIMER4->TIOCP_CFG |= (0x01<<0);//Read 1 : initiate software reset Write 1 : Reset ongoing
	while(DMTIMER4->TIOCP_CFG & (0x01<<0));	

	//2.Stop timer.
	timer2_wait_complete();
	DMTIMER4->TCLR &= ~(0x01<<0);

	//3. set timer.
	//3.1 Pre-scale clock and enable.
	timer4_wait_complete();
	DMTIMER4->TCLR &= ~(0x07<<2);
	timer4_wait_complete();
	DMTIMER4->TCLR |= ((0x01<<5) | (0x01<<2));//PRE=1,PTV=1,PS=4

#if 1
	//3.2 timer mode. overflow mode.
	timer2_wait_complete();
	DMTIMER4->TCLR &= ~(0x01<<6);
	//3.3 Auto-reload mode
	timer2_wait_complete();
	DMTIMER4->TCLR |=  (0x01<<1);
	
	//4. set load vale.
	timer2_wait_complete();
	DMTIMER4->TLDR = 0xFFFFE890;//0xFFFFE890
	DMTIMER4->TCRR = 0xFFFFE890;

	//set the PORTIMERPWM output pin and select negative pulse for pulse mode.  trigger on overflow
	DMTIMER4->TCLR |= (0x00<<7 | 0x01<<10 | 0x01<<12 | 0x00<<14);
	//7:默认高还是低；10：触发方式：溢出还是比较；12：脉冲还是高低电平交替；14：直接输出值
	
#endif

	timer4_wait_complete();//DMTimerWaitForWrite(0x1<<1);

}

void timer4_start(void)
{
	//4. set load vale.
	timer4_wait_complete();
	DMTIMER4->TLDR = 0xFFFFE890;
	DMTIMER4->TCRR = 0xFFFFE890;

	DMTIMER4->TCLR |=  (0x01<<0);
}

void timer4_stop(void)
{
	DMTIMER4->TCLR &= ~(0x01<<0);
}

static void timer4_int_enalbe(void)
{
	DMTIMER4->IRQEN_SET |= (0x01<<1); /* IRQ enable for Overflow */
}

static void timer4_int_clear(void)
{
	DMTIMER4->IRQSTS |= (0x07<<0);
}

static void timer_gpio_init(void)
{
	PRCM_CM_PER_GPIO5_CLKCTRL |= (0x02<<0);//CP511
	CTRL_CONF_I2C0_SDA &= ~(0x7<<0);
	CTRL_CONF_I2C0_SDA |=  (0x1<<0);
}

void  timer4_init(void)
{
	timer_gpio_init();

	timer4_clock_enable();

	timer4_config();

	//register_irq(IRQ_TIMER4, timer4_irq);

	//interrupt_init(IRQ_TIMER4);

	timer4_int_enalbe();
}

void timer4_irq(void)
{

	/*
	if(DMTIMER2->IRQSTS	& (0x01<<0))
	{
		uart_PutString("int Match");
	}
	else if(DMTIMER2->IRQSTS  & (0x01<<1)) 
	{
		uart_PutString("int overflow");
	}
	else
	{
		uart_PutString("int unknown");
	}
	*/
	
	timer4_int_clear();
}


