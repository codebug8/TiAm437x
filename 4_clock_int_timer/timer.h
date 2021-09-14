#ifndef  __TIMER_H__
#define  __TIMER_H__

extern void timer2_init(void);
extern void timer2_start(void);
extern void timer2_stop(void);
extern void timer2_irq(void);
extern void debug_timer2(char *str);

extern volatile unsigned int timer_delay_flag;


extern void timer4_init(void);
extern void timer4_start(void);
extern void timer4_stop(void);
extern void timer4_irq(void);



#endif
