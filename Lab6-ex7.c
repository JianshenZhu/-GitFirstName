#include<stdio.h>
int main()
{
	int x=1309;
	int *p = &x;//In this case the printer is assigned to NULL but the address cannot be NULL. To fix this problem I assigned the address of x to the printer and let it print the value of x.
	printf("\n The value of x is = %d",x);
	printf("\n The pointer points to the value = %d",*p);
	return 1;
}
