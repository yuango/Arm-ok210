CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

##INCLUDEDIR 	:= $(shell pwd)/include
##CFLAGS 		:= -Wall -O2 -fno-builtin
##CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)


CFLAGS 		:= -fno-builtin -nostartfiles -nostdlib
led_wtd.bin: start.o uart.o nand.o
	arm-linux-ld -Ttext 0x20008000 -e start -o nand.elf $^
	arm-linux-objcopy -O binary nand.elf nand.bin
	arm-linux-objdump -D nand.elf > nand_elf.dis


%.o : %.S
	arm-linux-gcc $(CFLAGS) -o $@ $< -c

%.o : %.c
	arm-linux-gcc $(CFLAGS) -o $@ $< -c 


#.PHONY : lig/libc.a
#lib/libc.a:
#	cd lib; make; cd ..
clean:
	@rm *.o *.elf *.bin *.dis -f
