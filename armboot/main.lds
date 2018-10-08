ENTRY(start)

SECTIONS
{
	. = 0x20004000;
	.text :
	{
		start.o(.text);
		*(.text);
	}
	.data :
	{
		*(.data);
	}
	bss_start = .;
	.bss :
	{
		*(.bss);
	}
	bss_end = .;
}
