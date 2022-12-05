#include "driver.h"
//driver 추가 라이브러리 스래드로 관리 해야 할듯
int LEDbyNum(int num)
{
    ledLibInit();
   

    while (1)
    {
        // scanf("%d", &num); //정수값 받아옴

        if (num < 0 || num > 8)
        { // 0~8 아닌 숫자 들어오면 오류메세지
            printf("Receive number Failed\r\n");
        }
        if (num == 0)
        { // num == 0이면 led 다 꺼짐
            ledOnOff(0, OFF);
            ledOnOff(1, OFF);
            ledOnOff(2, OFF);
            ledOnOff(3, OFF);
            ledOnOff(4, OFF);
            ledOnOff(5, OFF);
            ledOnOff(6, OFF);
            ledOnOff(7, OFF);
            ledOnOff(8, OFF);
        }

        while (num > 0 && num < 9) // 1~8값 받아올 때 각각의 led 점등
        {
            switch (num)
            {
            case 1:
                ledOnOff(0, ON);
                ledLibStatus();
                break;
            case 2:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledLibStatus();
                break;
            case 3:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledLibStatus();
                break;
            case 4:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledOnOff(3, ON);
                ledLibStatus();
                break;
            case 5:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledOnOff(3, ON);
                ledOnOff(4, ON);
                ledLibStatus();
                break;
            case 6:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledOnOff(3, ON);
                ledOnOff(4, ON);
                ledOnOff(5, ON);
                ledLibStatus();
                break;
            case 7:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledOnOff(3, ON);
                ledOnOff(4, ON);
                ledOnOff(5, ON);
                ledOnOff(6, ON);
                ledLibStatus();
                break;
            case 8:
                ledOnOff(0, ON);
                ledOnOff(1, ON);
                ledOnOff(2, ON);
                ledOnOff(3, ON);
                ledOnOff(4, ON);
                ledOnOff(5, ON);
                ledOnOff(6, ON);
                ledOnOff(7, ON);
                ledLibStatus();
                break;
            }
        }
    }
    ledLibExit();

    return 0;
}