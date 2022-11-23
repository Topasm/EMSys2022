#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define HELLO_DRIVER_NAME "/dev/hello1"

int main(int argc, char **argv)
{
    char data[4] = {'5', '6', '7', '8'};
    int fd;
   

    printf("enter test\n");
    // open driver
    fd = open(HELLO_DRIVER_NAME, O_RDWR);
    if (fd < 0)
    {
        printf(" open fail\n");
        perror("driver (/dev/hello1) open error.\n");
        return 1;
    }
    printf("open success\n");
  
    write(fd, &data, 4);
      int position = lseek(fd,0,SEEK_SET);
    printf("lseek Position%d\n" ,position);

   
    read(fd, data, 4);
     position = lseek(fd,0,SEEK_CUR);
    printf("lseek Position%d\n" ,position);
    position = lseek(fd,0,SEEK_SET);
    printf("lseek Position%d\n" ,position);

    printf("read value:%c%c%c%c\n", data[0], data[1], data[2], data[3]);
    
    

    for (int k=0;k<8;k++) {
        int request=1<<k;
        unsigned int inputCmd = _IO(0x55, request);
        printf("Enter CMD:%d->0x%08x \t\n",request,inputCmd);
        unsigned long returnValue = ioctl(fd, inputCmd, 0);
    }
    char array[20];
    unsigned int inputCmd = _IOW(0x55, 99, array);
    unsigned long returnValue = ioctl (fd, inputCmd, array);

    inputCmd = _IOW(0x55, 98, int);
    int count = 5;
    returnValue = ioctl (fd, inputCmd, &count);

  
    close(fd);
    return 0;
}
