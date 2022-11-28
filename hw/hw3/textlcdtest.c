
#include "textlcd.h"

int main(){
  
  const char* str1 = "test data1";
  const char* str2 = "test data2";
  txtlcd_Init();
  lcdtextwrite(str1, str2,1);
  lcdtextwrite(str1, str2,2);
  txtlcd_off();
  sleep(1);
  lcdtextwrite(str1, str2,0);

  return 0;
}