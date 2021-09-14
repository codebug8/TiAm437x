#ifndef  __INT_H__
#define  __INT_H__

typedef  void (*irq_func)(void);

extern void gic_init(void);
extern void interrupt_init(int irq);
extern void register_irq(int irq, irq_func func);
extern int get_irq(void);
extern void gic_int_clear(int irq);
extern void do_irq(void);

#endif

