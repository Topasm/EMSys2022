#ifndef _LED_H_
#define _LED_H_
int ledLibInit(void);
int ledOnOff(int ledNum, int onOff);
int ledStatus(void);
int ledLibExit(void);
#define LED_DRIVER_NAME "/dev/periled"
#define ON 1
#define OFF 0

#endif _LED_H_

