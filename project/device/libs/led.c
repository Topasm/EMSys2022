

#include "led.h"

static unsigned int ledValue = 0;
static int fd = 0;

int ledLibInit(void)
{
    fd = open("/dev/periled", O_WRONLY);
    ledValue = 0;
}

int ledOnOff(int ledNum, int onOff)
{
    int i = 1;
    i = i << ledNum;
    ledValue = ledValue & (~i);
    if (onOff != 0)
        ledValue |= i;
    write(fd, &ledValue, 4);
}

int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff(0, 0);
    close(fd);
}

void led(int SATU_MARI)
{

    if (SATU_MARI == 0)
    { // num == 0이면 led 다 꺼짐
        // printf("led0\n");
        ledOnOff(0, OFF);
        ledOnOff(1, OFF);
        ledOnOff(2, OFF);
        ledOnOff(3, OFF);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else if (SATU_MARI == 1)
    {
        // printf("led1\n");
        ledOnOff(0, ON);
        ledOnOff(1, OFF);
        ledOnOff(2, OFF);
        ledOnOff(3, OFF);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        //(10000);
    }

    else if (SATU_MARI == 2)
    {
        // printf("led2\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, OFF);
        ledOnOff(3, OFF);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else if (SATU_MARI == 3)
    {
        // printf("led3\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, OFF);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        //(10000);
    }

    else if (SATU_MARI == 4)
    {
        // printf("led4\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, ON);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else if (SATU_MARI == 5)
    {
        // printf("led5\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, ON);
        ledOnOff(4, ON);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else if (SATU_MARI == 6)
    {
        // printf("led6\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, ON);
        ledOnOff(4, ON);
        ledOnOff(5, ON);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else if (SATU_MARI == 7)
    {
        // printf("led7\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, ON);
        ledOnOff(4, ON);
        ledOnOff(5, ON);
        ledOnOff(6, ON);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // usleep(10000);
    }

    else if (SATU_MARI == 8)
    {
        // printf("led8\n");
        ledOnOff(0, ON);
        ledOnOff(1, ON);
        ledOnOff(2, ON);
        ledOnOff(3, ON);
        ledOnOff(4, ON);
        ledOnOff(5, ON);
        ledOnOff(6, ON);
        ledOnOff(7, ON);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }

    else
    { // num == 0이면 led 다 꺼짐
        // printf("led else\n");
        ledOnOff(0, OFF);
        ledOnOff(1, OFF);
        ledOnOff(2, OFF);
        ledOnOff(3, OFF);
        ledOnOff(4, OFF);
        ledOnOff(5, OFF);
        ledOnOff(6, OFF);
        ledOnOff(7, OFF);
        ledOnOff(8, OFF);
        // ledLibStatus();
        // usleep(10000);
    }
}
