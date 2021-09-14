#include "AM437X/AM437X_SOC.h"
#include "int.h"

static irq_func g_irq_func_array[211];

void gic_init(void)
{
	ICCPMR  = 0xff; 			// 不屏蔽任何中断级别的中断(越低越高)
	ICCBPR  = 0x0;
	ICCABPR = 0x0;

	ICDDCR = 0x1;				/* Enables the forwarding of pending interrupts from the Distributor to the CPU interfaces */
	ICCICR = 0x1;				/* Enables the signaling of interrupts by the CPU interface to the connected processor */

}

void interrupt_init(int irq)
{
	int n   = irq >> 5 ;   /* irq/32 */
	int bit = irq & 0x1f;  /* irq mod 32 */

	int m    = irq >> 2;
	int byte = irq & 0x3;
		
	ICDISR(n)  &= ~(1<<bit); 		// The corresponding interrupt is not-Secure
	ICDISER(n) |= (1<<bit); 		// 使能中断
	ICDICPR(n) |= (1<<bit); 		// 清中断

	ICDIPTR(m, byte) = 0x1;   /* irq ===> CPU interface 0 */
	
	//ICDICFR() = 0x55555555;
}

void register_irq(int irq, irq_func func)
{
	if (irq > 0 && irq < 211)
		g_irq_func_array[irq] = func;
}

int get_irq(void)
{
	return (ICCIAR & 0x3ff);
}

void gic_int_clear(int irq)
{
	int n   = irq >> 5 ;   /* irq/32 */
	int bit = irq & 0x1f;  /* irq mod 32 */

	ICDICPR(n) |= (1<<bit);
	ICCEOIR  = irq;
}

void do_irq(void)
{
	int irq = get_irq();
	if (g_irq_func_array[irq])
	{
		g_irq_func_array[irq]();
	}
	gic_int_clear(irq);
}

