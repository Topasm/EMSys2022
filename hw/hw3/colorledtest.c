
#include "colorled.h"
int main() {
pwmLedInit();
pwmSetPercent(50,0);   //blue
pwmSetPercent(50,1);  //green
pwmSetPercent(0,2);   //red
pwmInactiveAll();
return 0;
}
