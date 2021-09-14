#define CR_V	(1 << 13)	/* Vectors relocated to 0xffff0000	*/

.text
.global  _start
_start: 				
	/* 0 地址 */
	b reset                 /* 复位时,cpu跳到0地址 */
	b halt  /* cpu遇到不能识别的指令时 */
	b halt  /* 当执行swi指令时, 进入swi模 式 */
	b halt  /* 预取中止异常 */
	b halt  /* 数据访问异常 */
	b halt  /* 没用到 */
	ldr	pc, _irq            /* 0x18 中断异常 */
	b halt  /* 快中断异常 */

_irq:
	.word vector_irq
	
reset:	
	mrs r0, cpsr
	and r1, r0, #0x1f		@ mask mode bits
	teq r1, #0x1a		@ test for HYP mode
	bicne	r0, r0, #0x1f		@ clear all mode bits
	orrne	r0, r0, #0x13		@ set SVC mode
	orr r0, r0, #0xc0		@ disable FIQ and IRQ
	msr cpsr,r0
	
/*
 * Setup vector:
 */
	/* Set V=0 in CP15 SCTRL register - for VBAR to point to vector */
	mrc	p15, 0, r0, c1, c0, 0	@ Read CP15 SCTRL Register
	bic	r0, #CR_V		@ V = 0
	mcr	p15, 0, r0, c1, c0, 0	@ Write CP15 SCTRL Register

	/* Set vector address in CP15 VBAR register */
	ldr	r0, =_start
	mcr	p15, 0, r0, c12, c0, 0	@Set VBAR

/* 
 * 使能CPU IRQ中断 
 */
	mrs r0, cpsr	
	bic	r0,r0,#0x9f  /* 清cpsr的I位,M4~M0, enable IRQ */
	orr	r0,r0,#0x13
	msr	cpsr,r0      /* 进入SVC mode */


//设置栈
	ldr  sp,=0x40338e00
		
	bl  main

vector_irq:
	/* 1. 保存现场 */
	ldr sp, =(0x40338e00 - 8*1024)
	sub lr, lr, #4
	stmdb sp!, {r0-r12, lr}  /* lr就是swi的下一条指令地址 */

	/* 2. 处理异常 */
	bl do_irq
	
	/* 3. 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^表示把spsr恢复到cpsr */


halt:
	b  halt 




