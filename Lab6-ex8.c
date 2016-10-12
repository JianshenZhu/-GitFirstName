#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
	char *s, *dyn_s;
	int ln;
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = (char*)malloc(strlen(s)+1);//In this case the program what to output costumer’s input value but used the wrong format to assign the printer to malloc function.
	dyn_s = s;
	dyn_s[strlen(s)]='\0';
	printf("%s", dyn_s);//Missing the “%s” in the printf().
	return 0;
}

