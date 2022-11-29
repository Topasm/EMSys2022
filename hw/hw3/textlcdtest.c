
#include "textlcd.h"

int main(){
  
  const char* str1 = "hahaha";
  const char* str2 = "it works!!";
  txtlcd_Init();
  lcdtextwrite(str1, str2,1);
  sleep(1);
  lcdtextwrite(str1, str2,2);
  sleep(1);
  lcdtextwrite(str1, str2,0);

  return 0;
}