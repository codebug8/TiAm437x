
#ifndef  __KEY_H__
#define  __KEY_H__

//SP17;SP36、55
/****************************************************************************
                                 TI_BOARD_KEY
---------------------------------------------------------------------------
Key                                       Pin
---------------------------------------------------------------------------
SW6     PLAT_MTST5(E24:gpio5_13)         -PLAT_STST1(R24:spi4_d0/gpio5_5)      
SW7     PLAT_MTST5(E24:gpio5_13)         -PLAT_STST2(P24:spi4_d1/gpio5_6)
SW8     PLAT_STST1(P25:spi4_sclk/gpio5_4)-PLAT_STST1(R24:spi4_d0/gpio5_5)
SW9     PLAT_STST1(P25:spi4_sclk/gpio5_4)-PLAT_STST2(P24:spi4_d1/gpio5_6)
---------------------------------------------------------------------------
mode1: gpio5_13 high,gpio5_4 low,check gpio5_5 and gpio5_6.
mode2: gpio5_13 low,gpio5_4 high,check gpio5_5 and gpio5_6.
*****************************************************************************/


extern void key_init(void);

extern unsigned char get_key_val(void);


#endif


