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

/*clkout_channel：*/
#define CLKOUT_CLOSE       0
#define CLKOUT1            1
#define CLKOUT2            2
#define CLKOUT1_2          3

/*
* clkout_source1 and clkout_source2
* clkout_source2 can be set CLK_M_OSC
*/
#define CLK_M_OSC          1
#define CLK_32K_RTC        2
#define L3F_CLK            3
#define EXTDEV_PLL_CLKOUT  4
#define DDR_PHY_CLK        5
#define PER_CLKOUT_M2      6
#define PIXEL_CLK          7
#define MPU_PLL_CLKOUT     8

/*
* clkout1_div_osc：rang(0~3) for CLK_M_OSC.
*
* clkout1_div1 : rang(0~7) SYS_CLKOUT/(clkout1_div1+1) eg: 0->SYS_CLKOUT/1 1->SYS_CLKOUT/2 2->SYS_CLKOUT/3 
* clkout1_div2 : rang(0~5) SYS_CLKOUT/(2^clkout1_div2) eg: 0->SYS_CLKOUT/1 1->SYS_CLKOUT/2 3->SYS_CLKOUT/4 
*
* clkout2_div1 : rang(0~7) SYS_CLKOUT/(clkout2_div1+1) eg: 0->SYS_CLKOUT/1 1->SYS_CLKOUT/2 2->SYS_CLKOUT/3 
* clkout2_div2 : rang(0~5) SYS_CLKOUT/(2^clkout2_div2) eg: 0->SYS_CLKOUT/1 1->SYS_CLKOUT/2 3->SYS_CLKOUT/4 
*/

static struct clkout_struct {	
	unsigned char clkout_channel;

	unsigned char clkout_source1, clkout_source2;
		
	unsigned char clkout1_div_osc;
	unsigned char clkout1_div1, clkout1_div2;
	unsigned char clkout2_div1, clkout2_div2;
} rico_clkout;

static void debug_clkout(char *str);
static int set_clk_source1(struct clkout_struct rico_clkout);
static int set_clk_source2(struct clkout_struct rico_clkout);
static int set_clk_div1(struct clkout_struct rico_clkout);
static int set_clk_div2(struct clkout_struct rico_clkout);
static int set_clkout(struct clkout_struct rico_clkout);

int  main()
{
	uart_init();
	_100ask_printf("uart_init ok!\r\n");

	//设置引脚复用,模式0x03 clkout
	CTRL_CONF_XDMA_EVT_INTR0 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR0 |=  (0x03<<0);	

	CTRL_CONF_XDMA_EVT_INTR1 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR1 |=  (0x03<<0);	

	//设置输出参数
	rico_clkout.clkout_channel  = CLKOUT1_2;

	rico_clkout.clkout_source1  = L3F_CLK;
	rico_clkout.clkout_source2  = EXTDEV_PLL_CLKOUT;

	rico_clkout.clkout1_div_osc = 0;
	rico_clkout.clkout2_div1    = 0;
	rico_clkout.clkout2_div2    = 0;

	set_clkout(rico_clkout);

	debug_clkout("check clkout");
	
	while(1);

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

static int set_clk_source1(struct clkout_struct rico_clkout)
{
	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	switch(rico_clkout.clkout_source1)
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
		return 1;
	    break;
	}

	PRCM_CM_CLKOUT1_CTRL |= (0x01<<23);//SYS_CLKOUT1 is enabled

	return 0;
}


static int set_clk_source2(struct clkout_struct rico_clkout)
{
	PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
	
	switch(rico_clkout.clkout_source2)
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

	case CLK_M_OSC:
		_100ask_printf("set_clk_source2:Clkout2 can not be set CLK_M_OSC.\r\n"); 
		return 1;
		break;
		
	default:
		_100ask_printf("set_clk_source2:Select the clock source error.\r\n"); 
		return 1;
	    break;
	}

	PRCM_CM_CLKOUT2_CTRL |= (0x01<<16);//SYS_CLKOUT2 is enabled

	return 0;
}


static int set_clk_div1(struct clkout_struct rico_clkout)
{
	if((CLK_M_OSC == rico_clkout.clkout_source1 && rico_clkout.clkout1_div_osc > 3) || (rico_clkout.clkout1_div1 > 7 || rico_clkout.clkout1_div2 > 5))
	{
		_100ask_printf("set_clk_div1:Set the clock div error.\r\n"); 
		return 1;
	}

	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	if(CLK_M_OSC == rico_clkout.clkout_source1)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<20);	
		PRCM_CM_CLKOUT1_CTRL |=  (rico_clkout.clkout1_div_osc<<20);
	}
	else
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT1_CTRL |=  (rico_clkout.clkout1_div1<<4 | rico_clkout.clkout1_div2<<8);	
	}
		
	PRCM_CM_CLKOUT1_CTRL |= (0x01<<23);//SYS_CLKOUT1 is enabled

	return 0;
}

static int set_clk_div2(struct clkout_struct rico_clkout)
{
	if(CLK_M_OSC == rico_clkout.clkout_source2)
	{
		_100ask_printf("set_clk_div2:Clkout2 can not be set CLK_M_OSC.\r\n");
		return 1;
	}
		
	if(rico_clkout.clkout1_div1 > 7 || rico_clkout.clkout1_div2 > 5)
	{
		_100ask_printf("set_clk_div2:Set the clock div error.\r\n"); 
		return 1;
	}
	else
	{
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
		
		PRCM_CM_CLKOUT2_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT2_CTRL |=  (rico_clkout.clkout1_div1<<4 | rico_clkout.clkout1_div2<<8);	
	}
		
	PRCM_CM_CLKOUT2_CTRL |= (0x01<<16);//SYS_CLKOUT2 is enabled

	return 0;
}

static int set_clkout(struct clkout_struct rico_clkout)
{
	if(CLKOUT_CLOSE == rico_clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
			
	}
	else if(CLKOUT1 == rico_clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled

		set_clk_source1(rico_clkout);
		set_clk_div1(rico_clkout);
		
	}
	else if(CLKOUT2 == rico_clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled

		set_clk_source2(rico_clkout);
		set_clk_div2(rico_clkout);
		
	}	
	else if(CLKOUT1_2 == rico_clkout.clkout_channel)
	{

		set_clk_source1(rico_clkout);
		set_clk_div1(rico_clkout);
		set_clk_source2(rico_clkout);
		set_clk_div2(rico_clkout);
	}
	else
	{
		_100ask_printf("Set clkout channel error.\r\n");
		return 1;
	}

	return 0;
}

