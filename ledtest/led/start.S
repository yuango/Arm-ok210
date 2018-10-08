
.global led_init
.global delay
.equ GPH2_CON,0xe0200c40
.equ GPD0_CON,0xe02000a0
led_init:
	ldr r0,=GPD0_CON
	ldr r1,[r0]
	bic r1,r1,#(0xf<<0)

	@;GPC1CON,GPC1PUD
	ldr r0,=GPH2_CON
	ldr r1,[r0,#0]
	bic r1,r1,#(0xff<<8)
	orr r1,r1,#(0x11<<8)
	str r1,[r0,#0]

	ldr r1,[r0,#8]
	bic r1,r1,#(0xf<<4)
	str r1,[r0,#8]

loop:
	mov r0,#1
	bl led_ops
	
	mov r0,#0
	bl led_ops

	b loop

delay:
	sub r0,r0,#1
	cmp r0,#0
	bne delay
	mov pc,lr
