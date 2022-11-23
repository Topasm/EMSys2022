
#include "led.h"

   
int main(void)
{
    ledLibInit();

    for (int i = 0; i < 8; i++)
    {
        ledOnOff(i, ON);
        ledLibStatus();
        sleep(1);
        ledOnOff(i, OFF);
    }


    ledLibExit();
    return 0;
}