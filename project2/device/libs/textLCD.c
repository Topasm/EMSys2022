#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//#include "../libfbdev/libfbdev.h"
//#include "../lodepng/lodepng.h"
#include "../../device/libs/gyro.h"
#include "../../device/libs/textlcd.h"
#include "textLCD.h"

int textlcd_Init(void linenum, char *str)
{
   const char* str1 = "player Win!";
   const char* str2 = "You are Winner!";
   txtlcd_Init();
   lcdtextwrite(str1, str2,1);
   sleep(1);
   lcdtextwrite(str1, str2,2);
   txtlcd_off();
   txtlcd_Init();
   sleep(1);
   lcdtextwrite(str1, str2,0);
   return 0;
}