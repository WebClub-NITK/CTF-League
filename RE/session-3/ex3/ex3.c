#include <stdio.h>
#include <string.h>

void process_input(char *input)
{
	char buffer[100];

	/* Copy data into the buffer */
	strcpy(buffer, input);

	/* We don't do any processing. Lets just print it back */
	printf("buffer = %s\n", buffer);
}


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s [Any string you want]\n", argv[0]);
		return -1;
	}
	
	process_input(argv[1]);

	return 0;
}
