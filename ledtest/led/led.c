




void led_ops(int a)
{
	if(a)
	{
		volatile int *p=(int *)0xe0200c44;
		*p|=(1<<3);
	}
	else
	{
		volatile int *p=(int *)0xe0200c44;
		*p&=~(1<<3);
	}

	delay(0xff0000);
}
