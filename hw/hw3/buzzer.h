#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
char gBuzzerBaseSysDir[128];



int findBuzzerSysPath(void);
void buzzerInit(void);
void buzzerEnable(int bEnable);
void setFrequency(int frequency);
void buzzerPlaySong(int scale);
void buzzerStopSong(void);



#endif