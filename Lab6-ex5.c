#include<stdio.h>
#include<malloc.h>
void main()
{
    char *a;
    a = (char *)malloc(10);
    int i;
    char *b = "hello";
    while (i<6){
    *(a+i)=*(b+i);
     i++;
    }   
    printf("%s",a);

     free( a );
}
