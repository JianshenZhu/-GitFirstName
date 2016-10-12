 
#include<stdio.h>
#include<string.h>
void main()
{
    int i=0;
    char arr1[ 15 ] = "Trumantiger";
    char arr2[ 20 ];
    while(i<21){//In this case the GDB didn’t showing any fault message to me, but after the last character ‘A’, it showing some garbled stuff so I rechecked the program. I found that in the while loop it didn’t read the ‘\0’ of the array so that the array will not finish. That is also the reason when run the program it showing garbled stuff. I corrected it from 20 to 21 to make sure it will read the array completely. 
        arr2[ i ] = 'A';
	++i;
    }
    strcpy( arr1 , arr2 );
    printf("%s",arr1);
}
