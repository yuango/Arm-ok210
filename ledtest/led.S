

.equ GPC2_BASE,0xe0200080
@;纯汇编的宏定义常量
@;.global symbol 用于声明全局
@;两个以上对源文件之间对相互调用:用.global声明需要变为全局对别的文件可见的函数

#define GPC1_BASE 0xe0200080

start:
	@;GPC1CON:0Xe0200080 [15:12]=0b0001(0b:binary),GPC1_3(output)

	ldr r0,=GPC1_BASE
	ldr r1,[r0,#0]
	bic r1,r1,#(0xf<<12)	//clear bit
	orr r1,r1,#(1<<12)
	str r1,[r0,#0]

	@;GPC1PUD:0xe0200088 [7:6]=0b00
	ldr r1,[r0,#8]
	bic r1,r1,#(0x3<<6)
	str r1,[r0,#8]
	
loop:
	@;GPC1DAT:0xe0200084 [3]=0b1



	mov r0,#0xff0000
delay1:
	sub r0,r0,#1
	cmp r0,#0
	bne delay1

	@;GPC1DAT:0xe0200084 [3]=0b0



delay2:


	b loop
