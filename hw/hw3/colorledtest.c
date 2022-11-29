
#include "colorled.h"
int main() {
pwmLedInit();
pwmSetPercent(0,0);   //blue
pwmSetPercent(50,1);  //green
pwmSetPercent(50,2);   //red
pwmInactiveAll();
return 0;
}
