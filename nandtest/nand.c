
#define NFCONF		(*(volatile unsigned long *)0xb0e00000)
#define NFCONT		(*(volatile unsigned long *)0xb0e00004)
#define NFCMMD		(*(volatile unsigned long *)0xb0e00008)
#define NFADDR		(*(volatile unsigned long *)0xb0e0000c)
#define NFDATA		(*(volatile unsigned long *)0xb0e00010)

#define NFSTAT		(*(volatile unsigned long *)0xb0e00028)

#define NAND_PAGE_SIZE	(1<<11)

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
	int i = 9;
//	int b;
	unsigned int c;
	buf[0] = '0';
	buf[1] = 'x';

	while(a)
	{	
		c = a%16;
		if(c >= 10)
		{
			buf[i--] = c-10+'A';
		}
		else
		{
			buf[i--] = c+'0';
		}
		a = a/16;
	}

	if(i >= 2)
	{
		while(i > 1)
		{
			buf[i--] = '0';
		}
	}
	buf[10] = '\0';	
}

void nand_readid()
{
	nand_ce1_en();//ce1 enable
	NFCMMD = 0x90;//write 0x90 to nand flash command register
	NFADDR = 0x0;//write 0x0 to nand flash address register
	
	int i;
	for(i=0;i<256;i++)
	{
		;
	}

	unsigned int id1;
//	unsigned int id2;

	id1 = NFDATA;
//	id2 = NFDATA & 0xff;//read nand flash data register,read twice (40bit)

	
	nand_ce1_dis();

	puts("nand ID =");
	itoa(nand_itoa_buf,id1);//itoa();int to char
	puts(nand_itoa_buf);//puts();
//	itoa(nand_itoa_buf,id2);
//	puts(nand_itoa_buf);
	puts("\n");

}

void nand_clear_stat()
{
	NFSTAT |= (1<<4);//[4]=0 clear it
}

void nand_wait_RB()
{
	while(!(NFSTAT&(1<<4)));//when [4]=1,break
	return;
}

void nand_page_read(char *mem_addr,unsigned int nand_addr)
{
	unsigned int page_no;//?
	int i;
	int *ptr;//?

	page_no = nand_addr/NAND_PAGE_SIZE;
	
	nand_clear_stat();
	nand_ce1_en();
	
	NFCMMD = 0;
	
	NFADDR = 0;
	NFADDR = 0;
	NFADDR = (page_no&0xff);
	NFADDR = ((page_no>>8)&0xff);
	NFADDR = ((page_no>>16)&0xff);
	
	NFCMMD = 0x30;

	nand_wait_RB();

	ptr = (int *)mem_addr;
	for(i=0;i<NAND_PAGE_SIZE/4;i++)
	{
		ptr[i] = NFDATA;//每次传32位，4字节
	}
	nand_ce1_dis();
}

