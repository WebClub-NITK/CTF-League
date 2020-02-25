#include <stdio.h>
#include <stdlib.h>

int main()
{
	/* Declare the variable */
	int *ptr = NULL;
	
	/* Allocate memory for it */
	ptr = malloc(1000000000000);
	
	/* Give it a value */
	*ptr = 10;

	printf("ptr = %p, value = %d\n", ptr, *ptr);

	return 0;
}
