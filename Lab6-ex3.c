#include <stdio.h>

int factorial ( int num )
{   if (num>1){//In the factorial function, if it doesn’t have a limit then it will continue minus 1 and goes to the minimum value of the system. So in this case I add an if loop to this function and also add the ‘0’ case so that the program can get the correct and meaningful results for every value.
    return num * factorial( num - 1 );
	}
	else if (num == 0)
	return 1;
}

int main(void)
{
    int no,ans;
    printf("Enter the number \n");
    scanf( "%d", &no );
    ans = factorial( no );
    printf("The factorial is %d ", ans );
    return 0;
}
