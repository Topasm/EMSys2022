
#include "buzzer.h"

const int musicScale[MAX_SCALE_STEP] =  //음계를 주파수값으로 설정
    {
        262, // do
        294,
        330,
        349,
        392,
        440,
        494, // si
        523};

void doHelp(void)   //사용법 출력
{

    printf("Usage:\n");
    printf("buzzertest <buzzerNo> \n");
    printf("buzzerNo: \n");
    printf("do(1),re(2),mi(3),fa(4),sol(5),ra(6),si(7),do(8) \n");
    printf("off(0)\n");
}
int findBuzzerSysPath() //버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX의 XX 결정하는 함수
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
void buzzerEnable(int bEnable)    //주파수 출력 Enable
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    int fd = open(path, O_WRONLY);
    if (bEnable)
        write(fd, &"1", 1);
    else
        write(fd, &"0", 1);
    close(fd);
}

void setFrequency(int frequency)    //주파수 값 설정
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    int fd = open(path, O_WRONLY);
    dprintf(fd, "%d", frequency);
    close(fd);
}

void buzzerInit(void)
{
     if (findBuzzerSysPath() == 1)
    {
        printf("Path Find Failed\n");
        return 0;
    }
    buzzerEnable(3);

}

void buzzerExit(void)
{
    buzzerEnable(0);
}

void buzzerPlaySong(int scale)  //입력된 값으로 계이름별 주파수를 선택하여 부저 신호 출력
{
    if(scale> MAX_SCALE_STEP)
    {
        printf("buzzer over range\n");
    }
    setFrequency(musicScale[scale]);
    buzzerEnable(1);
    // C:0, D:1, ... , B:6, C:7
}


void buzzerStopSong(void)   //버저 소리를 멈추는 함수
{
    buzzerEnable(0);
}