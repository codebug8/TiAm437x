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
	b halt  /* 快中断异常 */


	
reset:	
	mrs r0, cpsr
	and r1, r0, #0x1f		@ mask mode bits
	teq r1, #0x1a		@ test for HYP mode
	bicne	r0, r0, #0x1f		@ clear all mode bits
	orrne	r0, r0, #0x13		@ set SVC mode
	orr r0, r0, #0xc0		@ disable FIQ and IRQ
	msr cpsr,r0
	

//设置栈
	ldr  sp,=0x40338e00
		
	bl  main



halt:
	b  halt 




