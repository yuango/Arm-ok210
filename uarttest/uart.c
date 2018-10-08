
#define GPA1CON 	(*(volatile unsigned long *)0xe0200020)

// UART

#define UFCON2		(*(volatile unsigned long *)0xe2900808)
#define UMCON2		(*(volatile unsigned long *)0xe290080c)
#define ULCON2		(*(volatile unsigned long *)0xe2900800)
#define UCON2		(*(volatile unsigned long *)0xe2900804)
#define UBRDIV2		(*(volatile unsigned long *)0xe2900828)
#define UDIVSLOT2		(*(volatile unsigned long *)0xe290082c)
#define UTRSTAT2		(*(volatile unsigned long *)0xe2900810)
#define UTXH2		(*(volatile unsigned long *)0xe2900820)
#define URXH2		(*(volatile unsigned long *)0xe2900824)

char shell_buf[256];

extern void nand_init();
extern void nand_readid();
//extern void do_cmd();

void uart_init(void)
{
	GPA1CON = 0x2222;
	UFCON2 = 0x0;
	UMCON2 = 0x0;
	ULCON2 = 0x3;
	UCON2 = 0x5;
	UBRDIV2 = 35;
	UDIVSLOT2 = 0x1;
}

char getc(void)
{
//	volatile int *p=(int *)0xe2900810;
	while(!(UTRSTAT2 & (1<<0)));//receive buffer empty,loop
//	volatile int *p=(int *)0xe2900824;
//	return (char)*p;
	return URXH2;
}

void putc(char c)
{
//	volatile int *p=(int *)0xe2900810;
	while(!(UTRSTAT2 & (1<<2)));//transmitt buffer not empty ,loop
//	volatile int *p=(int *)0xe2900820;
//	*p = c;

	UTXH2 = c;
//	if(c == '\r')
//	{	
//while(!(UTRSTAT2 & (1<<2)));
//UTXH2 = '\r';
//		putc('\n');
//	}
	
	if(c == '\n')
	{
		putc('\r');
	}	
}

void puts(char *s)
{
	char *b=s;
	while (*b != '\0')
	{
		putc(*b);
		b++;
	}
}

/*********************
void puts(const char *s)
{
	while(*s)
	{
		putc(*s++);
	}
}

***********************/

void gets()
{
	int n = 0;
	while(n < 256)
	{
		char c = getc();
		if(c!='\b')
		{
			if(c=='\r')
			{	
				putc('\n');
				break;
			}
			shell_buf[n++]=c;
			putc(c);
		}
		else //if(n>0)
		{
			if(n>0)
			{
			//	shell_buf[n]='';
			//	shell_buf[--n]='\0';
				n--;
				putc('\b');
				putc(' ');
				putc('\b');
			}
		}
		
	}

//delete ' ' before '\0'
	while(n>0)
	{
		n--;
		if(shell_buf[n]!=' ')
		{
			n++;
			break;
		}
	}
	shell_buf[n]='\0';
}

int strcmp(char *str1,const char *str2)
{
	while(*str1==' ')
	{
		str1++;
	}

	while(*str1)
	{
		if(*str1 != *str2)
		{
			return -1;
		}
		str1++;
		str2++;
	}
	
	if(*str2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void do_test()
{
	puts("test cmd finished\nand the space before or after the cmd is not effective!\n");
}

//shell_buf is empty or not
int nonecmd(const char *str)
{
	while(*str==' ')
	{
		str++;
	}
	
	if(*str)
	{
		return 0;
	}
	
	return -1;
}

void do_nandid()
{
	nand_init();//2 register,配置和控制寄存器
	nand_readid();//3 register
}

//test,nandid,boot
void parse_cmd()
{
	if(!(nonecmd(shell_buf)))
	{
		if(!strcmp(shell_buf,"test"))
		{
			do_test();
		}
		else if(!strcmp(shell_buf,"nandid"))
		{
			do_nandid();
		}
		else 
		{	
			puts("command not found\n");
		}
	}
}

void uart_run()
{
	uart_init();//8 registers
//	puts("##");
	for(;;)
	{
//		char c=getc();//get a char from input
//		putc(c);//output a char

		puts("#yuange-#");
		gets();
//		do_cmd();
		parse_cmd();//shell command
	}
}
