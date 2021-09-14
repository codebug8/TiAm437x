#include "AM437X/AM437X_SOC.h"
#include "clkout.h"
#include "uart.h"
#include "printf.h"


int clkout_init(void)
{
	//设置引脚复用,模式0x03 clkout
	CTRL_CONF_XDMA_EVT_INTR0 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR0 |=  (0x03<<0);	

	CTRL_CONF_XDMA_EVT_INTR1 &= ~(0x07<<0);
	CTRL_CONF_XDMA_EVT_INTR1 |=  (0x03<<0);	

	//设置输出参数
	rico_clkout.clkout_channel  = CLKOUT1;

	rico_clkout.clkout_source1  = L3F_CLK;
	rico_clkout.clkout_source2  = EXTDEV_PLL_CLKOUT;

	rico_clkout.clkout1_div_osc = 0;
	rico_clkout.clkout2_div1    = 0;
	rico_clkout.clkout2_div2    = 0;
	
	return 0;
}

int set_clk_source1(struct clkout_struct clkout)
{
	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	switch(clkout.clkout_source1)
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


int set_clk_source2(struct clkout_struct clkout)
{
	PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
	
	switch(clkout.clkout_source2)
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


int set_clk_div1(struct clkout_struct clkout)
{
	if((CLK_M_OSC == clkout.clkout_source1 && clkout.clkout1_div_osc > 3) || (clkout.clkout1_div1 > 7 || clkout.clkout1_div2 > 5))
	{
		_100ask_printf("set_clk_div1:Set the clock div error.\r\n"); 
		return 1;
	}

	PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
	
	if(CLK_M_OSC == clkout.clkout_source1)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x03<<20);	
		PRCM_CM_CLKOUT1_CTRL |=  (clkout.clkout1_div_osc<<20);
	}
	else
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT1_CTRL |=  (clkout.clkout1_div1<<4 | clkout.clkout1_div2<<8);	
	}
		
	PRCM_CM_CLKOUT1_CTRL |= (0x01<<23);//SYS_CLKOUT1 is enabled

	return 0;
}

int set_clk_div2(struct clkout_struct clkout)
{
	if(CLK_M_OSC == clkout.clkout_source2)
	{
		_100ask_printf("set_clk_div2:Clkout2 can not be set CLK_M_OSC.\r\n");
		return 1;
	}
		
	if(clkout.clkout1_div1 > 7 || clkout.clkout1_div2 > 5)
	{
		_100ask_printf("set_clk_div2:Set the clock div error.\r\n"); 
		return 1;
	}
	else
	{
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
		
		PRCM_CM_CLKOUT2_CTRL &= ~(0x07<<4 | 0x07<<8);	
		PRCM_CM_CLKOUT2_CTRL |=  (clkout.clkout1_div1<<4 | clkout.clkout1_div2<<8);	
	}
		
	PRCM_CM_CLKOUT2_CTRL |= (0x01<<16);//SYS_CLKOUT2 is enabled

	return 0;
}

int set_clkout(struct clkout_struct clkout)
{
	if(CLKOUT_CLOSE == clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled
			
	}
	else if(CLKOUT1 == clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT2_CTRL &= ~(0x01<<16);//SYS_CLKOUT2 is disabled

		set_clk_source1(clkout);
		set_clk_div1(clkout);
		
	}
	else if(CLKOUT2 == clkout.clkout_channel)
	{
		PRCM_CM_CLKOUT1_CTRL &= ~(0x01<<23);//SYS_CLKOUT1 is disabled

		set_clk_source2(clkout);
		set_clk_div2(clkout);
		
	}	
	else if(CLKOUT1_2 == clkout.clkout_channel)
	{

		set_clk_source1(clkout);
		set_clk_div1(clkout);
		set_clk_source2(clkout);
		set_clk_div2(clkout);
	}
	else
	{
		_100ask_printf("Set clkout channel error.\r\n");
		return 1;
	}

	return 0;
}

void debug_clkout(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
	_100ask_printf("PRCM_CM_CLKOUT1_CTRL      = 0x%x\r\n",PRCM_CM_CLKOUT1_CTRL);  
	_100ask_printf("PRCM_CM_CLKOUT2_CTRL      = 0x%x\r\n",PRCM_CM_CLKOUT2_CTRL);   
	_100ask_printf("PRCM_CM_DLL_CTRL          = 0x%x\r\n",PRCM_CM_DLL_CTRL);    
	_100ask_printf("******************************************************\r\n");
}