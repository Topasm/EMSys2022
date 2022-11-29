
#include "fnd.h"


#define FND_DRIVER_NAME      "/dev/perifnd"


#define ONE_SEG_DISPLAY_TIME_USEC   1000
// return 1 => success  , 0 => error
int fndDisp(int num , int dotflag)
{
   int fd;
   int temp,i;
   stFndWriteForm stWriteData;
   
   for (i = 0; i < MAX_FND_NUM ; i++ )
   {
      stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;  
      stWriteData.DataValid[i] = 1;
   }
   // if 6 fnd
   temp = num % 1000000;   stWriteData.DataNumeric[0]= temp /100000;
   temp = num % 100000;   stWriteData.DataNumeric[1]= temp /10000;
   temp = num % 10000;      stWriteData.DataNumeric[2] = temp /1000;
   temp = num %1000;      stWriteData.DataNumeric[3] = temp /100;
   temp = num %100;      stWriteData.DataNumeric[4] = temp /10;
                     stWriteData.DataNumeric[5] = num %10;

   //노드 열기                  
   fd = open(FND_DRIVER_NAME,O_RDWR);
   if ( fd < 0 )
   {
      perror("driver open error.\n");
      return 0;
   }   
   // struct에 data 입력
   write(fd,&stWriteData,sizeof(stFndWriteForm));
   close(fd);
   return 1;
}

int fndOff()
{
   int fd,i;
   //현재 FND 상태를 저장
   stFndWriteForm stWriteData;
   
   for (i = 0; i < MAX_FND_NUM ; i++ )
   {
      stWriteData.DataDot[i] =  0;  
      stWriteData.DataNumeric[i] = 0;
      stWriteData.DataValid[i] = 0;
   }
   fd = open(FND_DRIVER_NAME,O_RDWR);
   if ( fd < 0 )
   {
      perror("driver open error.\n");
      return 0;
   }   
   write(fd,&stWriteData,sizeof(stFndWriteForm));
   close(fd);
   return 1;
}