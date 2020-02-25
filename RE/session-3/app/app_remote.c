#include <stdio.h>

int main()
{
	char name[8];
	char password[8] = {0};
	unsigned long int *int_pwd = (unsigned long int *)password;

	printf("Name: ");
	fflush(stdout);

	scanf("%s", name);
	fflush(stdin);

	if(*int_pwd != 0)
	{
		printf("You got access!\n");
		fflush(stdout);
		return 0;
	}
	else
	{
		printf("No access for you!\n");
		fflush(stdout);
		return 0;
	}

	return 0;
}
