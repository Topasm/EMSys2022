// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/ioctl.h>
// #include <ctype.h>
// #include <sys/ipc.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>



// #define LED_DRIVER_NAME      "/dev/periled"

// void doHelp(void)
// {
//    printf("Usage:\n");
//    printf("ledtest <hex byte>  :data bit0 operation 1=>on 0=>off\n");
//    printf("ex) ledtest 0x04 ;3th led on\n");
//    printf("    ledtest 0x05 ;4th and 1th led on\n");
//    printf("    ledtest 0xff ;all led on\n");
//    printf("    ledtest 0x00 ;all led off\n");
// }



// int main(int argc , char **argv)
// {
//    unsigned int data = 0;   
   
//    int fd;
   
//    if (argc < 2 )
//    {
//       perror(" Args number is less than 2\n");
//       doHelp();
//       return 1;
//    }
   
//    data = strtol(argv[1],NULL,16);
//    printf("wrate data :0x%X\n", data);
   
//    // open  driver 
//    fd = open(LED_DRIVER_NAME,O_RDWR);
//    if ( fd < 0 )
//    {
//       perror("driver (//dev//cnled) open error.\n");
//       return 1;
//    }
//    write(fd,&data,4);

//    close(fd);
   
//    return 0;
// }



#include "led.h"

   
int main(void)
{
    ledLibInit();

    for (int i = 0; i < 8; i++)
    {
        ledOnOff(i, ON);
        ledLibStatus();
        sleep(1);
    }


    ledLibExit();
    return 0;
}