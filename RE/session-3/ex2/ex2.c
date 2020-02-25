#include <stdio.h>

/* Simple swap function */
void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

int main()
{
    int n;
    scanf("%d", &n);

    int a[n];
	
    /* Take input */
    for(int i = 0; i < n; i++)
	scanf("%d", &a[i]);
    
    /* What does this code do? */
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            if(a[j] > a[j+1])
                swap(&a[j], &a[j+1]);
        }
    }
    
    /* Output this */
    for(int i=0; i<n; i++)
	printf("%d\t", a[i]);

    printf("\n");
}
