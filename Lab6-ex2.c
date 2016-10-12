#include <stdio.h>
void main()
{
    char p[ 6 ] = "Mizzou";//Because of if define the string as a string literal, it cannot be changed. So in this case we should define p as an array instead of a printer so that the characters in the array can be changed.
    p[ 3 ] = 'P';
    printf("%s",p);
}
