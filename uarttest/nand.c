
#define NFCONF		(*(volatile unsigned long *)0xb0e00000)
#define NFCONT		(*(volatile unsigned long *)0xb0e00004)
#define NFCMMD		(*(volatile unsigned long *)0xb0e00008)
#define NFADDR		(*(volatile unsigned long *)0xb0e0000c)
#define NFDATA		(*(volatile unsigned long *)0xb0e00010)

extern void puts(char *);

char nand_itoa_buf[10];

void nand_init()
{
	NFCONF = 0xfff2;//nand flash configuration register
	NFCONT = 0xc000c7;//nand flash control register
}

void nand_ce1_en()
{
	NFCONT &= ~(1<<1);
}

void nand_ce1_dis()
{
	NFCONT |= (1<<1);
}

void itoa(char *buf,unsigned int a)
{
	int i;
	int d;
	unsigned int c;

	if(a > 0xff)
	{
		i = 1;
		buf[0] = '0';
		buf[1] = 'x';
		buf[10] = '\0';	
	}
	else
	{
		i = 0;
		buf[2] = '\0';
	}

//	buf[0] = '0';
//	buf[1] = 'x';

	while(a)
	{	
		c = a%16;
		if(c >= 10)
		{
			buf[2*i+1] = c-10+'A';
		}
		else
		{
			buf[2*i+1] = c+'0';
		}
		a = a/16;
		if(a)
		{
			d = a%16;
			if(d >= 10)
			{
				buf[2*i] = d-10+'A';
			}
			else
			{
				buf[2*i] = d+'0';
			}
			
			a = a/16;
		}
		else
		{
			buf[2*i] = '0';
		}
		
		i++;
	}
/******************************************
	if(i >= 2)
	{
		while(i > 1)
		{
			buf[i--] = '\0';
		}
	}
*****************************************/		
}

void nand_readid()
{
	nand_ce1_en();
	NFCMMD = 0x90;//write 0x90 to nand flash command register
	NFADDR = 0x0;//write 0x0 to nand flash address register
	
	int i;
	for(i=0;i<256;i++)
	{
		;
	}

	unsigned int id1;
	unsigned int id2;

	id1 = NFDATA;
	id2 = NFDATA & 0xff;//read nand flash data register,read twice (40bit)

	
	nand_ce1_dis();

	puts("nand ID =");
	itoa(nand_itoa_buf,id1);//itoa();int to char
	puts(nand_itoa_buf);//puts();
	itoa(nand_itoa_buf,id2);
	puts(nand_itoa_buf);
	puts("\n");

}
