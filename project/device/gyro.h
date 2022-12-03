#ifndef _GYRO_H_
#define _GYRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int get_dx(void);

#endif