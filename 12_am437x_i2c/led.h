
#ifndef  __LED_H__
#define  __LED_H__

/**************************************************
                  TI_BOARD_LED
---------------------------------------------------
Ball     Color       Mode             Pin
---------------------------------------------------
H24     D7_Blue      0x07     uart3_txd(GPIO5_3)
H25     D8_Blue      0x07     uart3_rxd(GPIO5_2)
K24     D9_Green     0x07     uart3_rtsn(GPIO5_1)
H22     D10_Red      0x07     uart3_ctsn(GPIO5_0)
**************************************************/

extern void led_init(void);

extern void led_switch(unsigned char on_off);
extern void led0_switch(unsigned char on_off);
extern void led1_switch(unsigned char on_off);
extern void led2_switch(unsigned char on_off);
extern void led3_switch(unsigned char on_off);

#endif


