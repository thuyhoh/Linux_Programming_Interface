// commands ./cp 

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024

int main(int args, char** argv)
{
    int fd_dst = -1, fd_src = -1;
    int buff;
    int index = 0;
    if(args<= 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("cmd error \n\"./cp dstfile srcfile \"\n-> copy regular file src to dst \n");
        return 0;
    }
    if(fd_dst = open(argv[2], O_CREAT|O_RDWR, 0667) == -1)
    {
        printf("opening file:%s false\n", argv[2]);
    }
    if(fd_src = open(argv[3], O_RDWR) == -1)
    {
        printf("opening file:%s false\n", argv[2]);
    }
   // lseek(fd_src, index, SEEK_SET);
   int numRead = 0; 
   while((numRead = read(fd_src, &buff, BUFF_SIZE))> 0)
    {
        if(write(fd_dst,&buff, 1) != numRead)
        {
            printf("couldn't write whole buffer\n");
        }
    }
    if(numRead == -1) printf("error read\n");
    if(close(fd_dst) == -1) printf("error close file %s failse\n", argv[2]);
    if(close(fd_src) == -1) printf("error close file %s failse\n", argv[3]);  
    exit(EXIT_SUCCESS);
}
