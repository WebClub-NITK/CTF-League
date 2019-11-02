#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sigsegv_handler(int sig)
{
	printf("You got a shell!!\n");
	system("/bin/sh");
}

void vuln(char *input)
{
	char buf[16];
	strcpy(buf, input);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegv_handler);

	if(argc != 2)
	{
		printf("Usage: %s your_string\n", argv[0]);
		return -1;
	}

	vuln(argv[1]);

	return 0;
}
