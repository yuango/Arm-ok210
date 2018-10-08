.text

.global start

.word 0x2000
.word 0x0
.word 0x0
.word 0x0

start:
	msr cpsr_c,#0xd3
	ldr sp,=0xd0036000
	sub sp,sp,#12
	@;....自写初始化...clk,dram,sp,bss

	bl uart_run
	b .
