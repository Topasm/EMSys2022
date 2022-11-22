#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/”
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

//
char gBuzzerBaseSysDir[128]; // /sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static int fdEnable;
static int fdFrequency;

const int musicScale[MAX_SCALE_STEP] = // Just Intonation : 13 sounds
    {
        262, // C
        277, // C#
        294, // D
        311, // D#
        330, // E
        349, // F
        370, // F#
        392, // G
        415, // G#
        440, // A
        466, // A#
        494, // B
        523 // C
    };

int findBuzzerSysPath(void) //버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것
{
    DIR *dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL)
    {
        while (1)
        {
            struct dirent *dir_entry;
            dir_entry = readdir(dir_info);
            if (dir_entry == NULL)
                break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
            {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir, "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name);
            }
        }
    }
    printf("find %s\n", gBuzzerBaseSysDir);
    return ifNotFound;
}

int buzzerInit(void)
{
    if (findBuzzerSysPath() == 1)
    {
        printf("Path Find Failed\r\n");
        return 0;
    }

    char path[256];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    fdEnable = open(path, O_WRONLY);

    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    fdFrequency = open(path, O_WRONLY);

    printf("File Successfully Opened!\r\n");

    return 1;
}

void buzzerEnable(int bEnable)
{
    if (bEnable)
        write(fdEnable, "1", 1);
    else
        write(fdEnable, "0", 1);
}

void setFrequency(int frequency)
{
    dprintf(fdFrequency, "%d", frequency);
}

void buzzerExit(void)
{
    buzzerEnable(0);
	close(fdEnable);
	close(fdFrequency);
}

void buzzerPlaySong(int scale) // C:0, C#:1, ... , A:9, A#:10, B:11
{
    setFrequency(musicScale[scale]);
    buzzerEnable(1);
}

void buzzerStopSong(void)
{
    buzzerEnable(0);
}

