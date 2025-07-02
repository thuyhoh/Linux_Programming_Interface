#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <string.h>
#include <math.h>

int atoi(char *str)
{
    int result = 0;
    int i = 0;
    while(i < strlen(str))
    {
        result = result * 10 + (*(str+i) - '0');
        i++;
    }
    return result;
}

int main(int args, char *argv[])
{
    int fd;
    if(args <= 3 || strcmp(argv[0], "--help")) printf("./seek file s<offset> {r<Byte>/R<Byte>|w<string>}\n");
    fd = open(argv[1], O_RDWR);
    if(fd == -1) printf("error: open file failse\n");
    
    lseek(fd, atoi(argv[2]++), SEEK_SET);
    printf("seek successed\n");
    return 0;
}

