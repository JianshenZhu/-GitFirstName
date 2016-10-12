#include<stdio.h>
#include<malloc.h>
void main()
{
    char *a;
    a = (char *)malloc(10);//In this case the GDB was showing that it has an invalid printer in the program, I found that there is a <malloc.h> included in the head so I realized that the free function is combined with malloc function and is used in heap not stack, free function is used to deallocate the memory once you don’t want it anymore. So I defined "a" by malloc function and then free the memory. 
    int i;
    char *b = "hello";
    while (i<6){
    *(a+i)=*(b+i);
     i++;
    }   
    printf("%s",a);

     free( a );
}
