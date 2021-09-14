#ifndef  __CLKOUT_H__
#define  __CLKOUT_H__

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
struct clkout_struct {
	unsigned char clkout_channel;

	unsigned char clkout_source1, clkout_source2;
		
	unsigned char clkout1_div_osc;
	unsigned char clkout1_div1, clkout1_div2;
	unsigned char clkout2_div1, clkout2_div2;
}rico_clkout;;

extern int clkout_init(void);
extern int set_clk_source1(struct clkout_struct clkout);
extern int set_clk_source2(struct clkout_struct clkout);
extern int set_clk_div1(struct clkout_struct clkout);
extern int set_clk_div2(struct clkout_struct clkout);
extern int set_clkout(struct clkout_struct clkout);
extern void debug_clkout(char *str);


#endif


