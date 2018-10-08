/bin/sh

arm-linux-gcc -c led.S
#先生成.o文件
arm-linux-gcc -Ttext 0x20008000 -nostartfiles -nostdlib led.o -o led
#0x20008000为运行内存地址
arm-linux-objcopy -O binary led led.bin
#生成只有机器码对纯二进制文件
#-e start 告诉编译器入口函数为start,但是首先需要用.global start
#而编译器默认入口为_start函数，所以可以编写成_start函数
