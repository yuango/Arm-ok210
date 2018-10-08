
#define N	4

extern void do_test();
extern void do_nandid();
extern void puts(char *);
extern char shell_buf[256];
extern int strcmp(char *,const char *);
extern int nonecmd(const char *);
extern void do_nandread();
extern void do_bootlinux();


typedef struct _Tcmd
{
	const char *cmd_name;
	void (*cmd_func)(void);
}cmd_t;

void cmd_do_test(void)
{
	do_test();
}

void cmd_do_nandid(void)
{
	do_nandid();
}

void cmd_do_nandread()
{
	do_nandread();
}

void cmd_do_bootlinux()
{
	do_bootlinux();
}

const cmd_t cmd_list[]=
{
	{"test",cmd_do_test},
	{"nandid",cmd_do_nandid},
	{"nandread",cmd_do_nandread},
	{"bootlinux",cmd_do_bootlinux},
};

const cmd_t *find_cmd(char *p)
{
	int i;
	for(i=0;i<N;i++)
	{
		if(!(strcmp(p,cmd_list[i].cmd_name)))
		{
			return &(cmd_list[i]);
		}	
	}
	
	return 0;
}

void do_cmd()
{
	const cmd_t *cmd_ptr;
	if(!(nonecmd(shell_buf)))
	{
		cmd_ptr = find_cmd(shell_buf);
		if(0 == cmd_ptr)
		{
			puts("command not found!\n");
		}
		else
		{
			cmd_ptr->cmd_func();
		}
	}
}
