CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

##INCLUDEDIR 	:= $(shell pwd)/include
##CFLAGS 		:= -Wall -O2 -fno-builtin
##CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)


CFLAGS 		:= -fno-builtin -nostartfiles -nostdlib
led_wtd.bin: start.o cmd.o uart.o nand.o
	arm-linux-ld -e start -o nandt.elf $^
	arm-linux-objcopy -O binary nandt.elf nandt.bin
	arm-linux-objdump -D nandt.elf > nandt_elf.dis


%.o : %.S
	arm-linux-gcc $(CFLAGS) -o $@ $< -c

%.o : %.c
	arm-linux-gcc $(CFLAGS) -o $@ $< -c 


#.PHONY : lig/libc.a
#lib/libc.a:
#	cd lib; make; cd ..
clean:
	@rm *.o *.elf *.bin *.dis -f
