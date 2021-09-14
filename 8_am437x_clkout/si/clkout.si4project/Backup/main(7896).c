/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: AM437X裸机clkout
    > Created Time: 20170811
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "printf.h"
#include "key.h"


#define CLKOUT1            1
#define CLKOUT2            2

#define CLK_M_OSC          1
#define CLK_32K_RTC        2
#define L3F_CLK            3
#define EXTDEV_PLL_CLKOUT  4
#define DDR_PHY_CLK        5
#define PER_CLKOUT_M2      6
#define PIXEL_CLK          7
#define MPU_PLL_CLKOUT     8

static struct div_struct {	
	unsigned char div_osc;
	unsigned char div1;
	unsigned char div2;
};


int  loop_judge_register_bits(unsigned  int reg_addr, unsigned  int bits, unsigned  int expected_val);
static void debug_clkout(char *str);

unsigned char set_clk_source1(unsigned char clk_source);
unsigned char set_clk_source2(unsigned char clk_source);

unsigned char set_clk_div1(unsigned char clk_source, struct div_struct div);
unsigned char set_clk_div2(unsigned char clk_source, struct div_struct div);

unsigned char single_clkout(unsigned char channel, unsigned char clk_source, struct div_struct div);
unsigned char double_clkout(unsigned char clk_source1,unsigned char clk_source2, struct div_struct div1, struct div_struct div2);

int  main()
{

	struct div_struct clk_div;
		
	uart_init();
	_100ask_printf("uart_init ok!\r\n");

	//1.设置模块时钟，猜测不需要

	//2.设置引脚复用,模式0x03 clkout
	CTRL_CONF_XDMA_EVT_INTR0 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR0 |=  (0x03<<0);	

	CTRL_CONF_XDMA_EVT_INTR1 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR1 |=  (0x03<<0);	


	PRCM_CM_RTC_CLKCTRL &= ~(0x3<<0);
	PRCM_CM_RTC_CLKCTRL |= (0x01<<1);
	PRCM_CM_RTC_CLKSTCTRL &= ~(0x3<<0);

	

	//3.模块功能设置
	//3.1 
	//PRCM_CM_CLKOUT1_CTRL //0h (R/W) = Selects Master Osc[CLK_M_OSC].

	clk_div.div_osc = 3;
	clk_div.div1 = 0;
	clk_div.div2 = 0;
	
	single_clkout(CLKOUT1, CLK_M_OSC, clk_div);
	single_clkout(CLKOUT2, CLK_32K_RTC, clk_div);

	debug_clkout("clkout set ok.\n\r");
	while(1)
	{

	}
	return 0;
}


/*********************************************************************************
   *Function:     loop_judge_register_bits
   *Description： 循环判断某个寄存器的值为多少
   *Input:        寄存器地址，哪些bit位，期待值
   *Output:       \
   *Return:       0
   *Others:       \
**********************************************************************************/
int  loop_judge_register_bits(unsigned  int reg_addr, unsigned  int bits, unsigned  int expected_val)
{
	volatile unsigned  int  reg=reg_addr;	
	unsigned  int  tmp=0;//volatile unsigned  int  tmp=0;
	
	do
	{
		tmp = reg;
		tmp = tmp & (bits); 
	}
	while(expected_val !=  tmp);//判断

	return 0;
}


/*********************************************************************************
   *Function:     debug_clkout
   *Description： 调试程序打印出全部相关寄存器
   *Input:        字符串标记
   *Output:       \
   *Return:       0
   *Others:       将传入参数由整型改为字符型
**********************************************************************************/
static void debug_clkout(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
	_100ask_printf("PRCM_CM_CLKOUT1_CTRL      = 0x%x\r\n",PRCM_CM_CLKOUT1_CTRL);  
	_100ask_printf("PRCM_CM_CLKOUT2_CTRL      = 0x%x\r\n",PRCM_CM_CLKOUT2_CTRL);   
	_100ask_printf("PRCM_CM_DLL_CTRL          = 0x%x\r\n",PRCM_CM_DLL_CTRL);    
	_100ask_printf("******************************************************\r\n");
}


unsigned char set_clk_source1(unsigned char clk_source)
{
	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	switch(clk_source)
	{
	case CLK_M_OSC:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16);
		PRCM_CM_CLKOUT1_CTRL |=  (0x00<<16);
		break;
		
	/*这样的CLK_32K_RTC分频少；
	case CLK_32K_RTC:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 | 0x01<<24);
		PRCM_CM_CLKOUT1_CTRL |=  (0x01<<16 | 0x01<<24);
		break;
	*/

	case EXTDEV_PLL_CLKOUT:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16);
		PRCM_CM_CLKOUT1_CTRL |=  (0x03<<16);
		break;	

	case CLK_32K_RTC:
		PRCM_CM_CLKOUT1_CTRL &= ~( 0x07<<0 | 0x03<<16  | 0x01<<24);
		PRCM_CM_CLKOUT1_CTRL |=  ( 0x00<<0 | 0x02<<16  | 0x01<<24);
		break;

	case L3F_CLK:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 );
		PRCM_CM_CLKOUT1_CTRL |=  (0x02<<16 | 0x01<<0);
		break;

	case DDR_PHY_CLK:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 | 0x07<<0);
		PRCM_CM_CLKOUT1_CTRL |=  (0x02<<16 | 0x02<<0);
		break;

	case PER_CLKOUT_M2:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 | 0x07<<0);
		PRCM_CM_CLKOUT1_CTRL |=  (0x02<<16 | 0x03<<0);
		break;

	case PIXEL_CLK:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 | 0x07<<0);
		PRCM_CM_CLKOUT1_CTRL |=  (0x02<<16 | 0x04<<0);
		break;
	
	case MPU_PLL_CLKOUT:
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<16 | 0x07<<0);
		PRCM_CM_CLKOUT1_CTRL |=  (0x02<<16 | 0x05<<0);
		break;
		
	default:
		_100ask_printf("set_clk_source1:Select the clock source error.\r\n"); 
	    break;
	}

	PRCM_CM_CLKOUT1_CTRL |= (0x01<<23);//SYS_CLKOUT1 is enabled

	return 0;
}


unsigned char set_clk_source2(unsigned char clk_source)
{
	PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
	
	switch(clk_source)
	{		
	case CLK_32K_RTC:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x00<<0);
		break;

	case L3F_CLK:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x01<<0);
		break;
		
	case DDR_PHY_CLK:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x02<<0);
		break;

	case PER_CLKOUT_M2:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x03<<0);
		break;

	case PIXEL_CLK:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x04<<0);
		break;
	
	case MPU_PLL_CLKOUT:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x05<<0);
		break;

		case EXTDEV_PLL_CLKOUT:
		PRCM_CM_CLKOUT2_CTRL &= ~(0x03<<0);
		PRCM_CM_CLKOUT2_CTRL |=  (0x06<<0);
		break;
		
	default:
		_100ask_printf("set_clk_source2:Select the clock source error.\r\n"); 
	    break;
	}

	PRCM_CM_CLKOUT2_CTRL |= (0x01<<16);//SYS_CLKOUT2 is enabled

	return 0;
}


unsigned char set_clk_div1(unsigned char clk_source, struct div_struct div)
{
	if((CLK_M_OSC == clk_source && div.div_osc > 3) || (div.div1 > 7 || div.div2 > 5))
	{
		_100ask_printf("set_clk_div1:Set the clock div error.\r\n"); 
		return 1;
	}

	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	if(CLK_M_OSC == clk_source)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<20);	
		PRCM_CM_CLKOUT1_CTRL |=  (div.div_osc <<20);
	}
	else
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT1_CTRL |=  (div.div1<<4 | div.div2<<8);	
	}
		
	PRCM_CM_CLKOUT1_CTRL |= (0x01<<23);//SYS_CLKOUT1 is enabled

	return 0;
}

unsigned char set_clk_div2(unsigned char clk_source, struct div_struct div)
{
	if(CLK_M_OSC == clk_source)
	{
		_100ask_printf("set_clk_div2:Select the clock source error.\r\n");
		return 1;
	}
		
	if(div.div1 > 7 || div.div2 > 5)
	{
		_100ask_printf("set_clk_div2:Set the clock div error.\r\n"); 
		return 1;
	}
	else
	{
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
		
		PRCM_CM_CLKOUT2_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT2_CTRL |=  (div.div1<<4 | div.div2<<8);	
	}
		
	PRCM_CM_CLKOUT2_CTRL |= (0x01<<16);//SYS_CLKOUT2 is enabled

	return 0;
}


unsigned char single_clkout(unsigned char channel, unsigned char clk_source, struct div_struct div)
{
	
	if(CLKOUT1 == channel)
	{
		set_clk_source1(clk_source);
		set_clk_div1(clk_source, div);
	}
	else if(CLKOUT2 == channel)
	{
		set_clk_source2(clk_source);
		set_clk_div2(clk_source, div);
	}
	else 
	{
		_100ask_printf("single_clkout:Select the clock channel error.\r\n");
	}
		 
	return 0;
}

unsigned char double_clkout(unsigned char clk_source1,unsigned char clk_source2, struct div_struct div1, struct div_struct div2)
{
	set_clk_source1(clk_source1);
	set_clk_source2(clk_source2);
	set_clk_div1(clk_source1, div1);
	set_clk_div2(clk_source2, div2);

	return 0;
}

