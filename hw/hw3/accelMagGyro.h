#ifndef _ACCELMAGYRO_H_
#define _ACCELMAGYRO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h> //이건 뭐하는 헤더파일인지...?
#include <unistd.h>    // for open/close
#include <fcntl.h>     // for O_RDWR
#include <sys/ioctl.h> // for ioctl

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"



int init_accel(void);
int init_mag(void);
int init_gyro(void);





#endif