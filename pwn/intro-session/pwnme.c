#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sigsegv_handler(int sig)
{
	printf("You got a shell!!\n");
	fflush(stdout);

	system("/bin/sh");
}

void vuln()
{
	char buf[16];
	printf("Enter any string you want!");
	fflush(stdout);

	gets(buf);
	fflush(stdin);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegv_handler);

	vuln();

	return 0;
}
