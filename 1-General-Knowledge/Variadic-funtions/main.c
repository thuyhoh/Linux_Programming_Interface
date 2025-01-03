#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int sum(int count, ...);

int main(void)
{
    printf("%d\n", sum(2,1,3));
    printf("%d", sum(10,1,2,3,4,5,6,7,8,9,0));
    return 0;
}

int sum(int count, ...)
{
    va_list args;
    va_start(args, count);
    int i, s = 0;
    for(i = 0; i< count; i++)
    {
        int x = va_arg(args, int);
        s += x;
    }
    va_end(args);
    return s;
}
