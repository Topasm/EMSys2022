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
#define BUZZER_FREQUENCY_NAME "frequency"#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>    // for open/close
#include <fcntl.h>     // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event1" //실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices" // PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static int fd = 0;
static int msgID = 0;
static pthread_t buttonTh_id;
char buttonPath[256] = {0,};


int buttonInit(void)
{
if (probeButtonPath(buttonPath) == 0)
return 0;
fd=open (buttonPath, O_RDONLY);
msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
return 1;
}
//buttonThFunc 쓰레드 함수 작성 필요
//while(1){을 돌면서 / read(); / msgsnd(); }

static void *buttonThFunc(void)
{
    BUTTON_MSG_T Data;
    Data.messageNum = 1;
    struct input_event stEvent;
    while (1)
    {
        read(fd, &stEvent, sizeof(stEvent));
        if ((stEvent.type == EV_KEY) && (stEvent.value == 0))
        {
            Data.keyInput = stEvent.code;
            msgsnd(msgID, &Data, sizeof(Data)-4, 0);
        }
    }
}

int probeButtonPath(char *newPath)
{
int returnValue = 0; //button에 해당하는 event#을 찾았나?
int number = 0; //찾았다면 여기에 집어넣자
FILE *fp = fopen(PROBE_FILE,"rt"); //파일을 열고
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"
while(!feof(fp)) //끝까지 읽어들인다.
{
char tmpStr[200]; //200자를 읽을 수 있게 버퍼
fgets(tmpStr,200,fp); //최대 200자를 읽어봄
//printf ("%s",tmpStr);
if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
{
printf("YES! I found!: %s\r\n", tmpStr);
returnValue = 1; //찾음
}

if (
(returnValue == 1) && //찾은 상태에서
(strncasecmp(tmpStr, HAVE_TO_FIND_2, 
strlen(HAVE_TO_FIND_2)) == 0) //Event??을 찾았으면
)
{
printf ("-->%s",tmpStr);
printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
number = tmpStr[strlen(tmpStr)-3] - '0'; 
//Ascii character '0'-'9' (0x30-0x39) 
//to interger(0)
break;
}
}
fclose(fp);
if (returnValue == 1)
sprintf (newPath,"%s%d",INPUT_DEVICE_LIST,number);
return returnValue;
}

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
        330, // E/home/soomin/vscode/linux_kernel//home/soomin/vscode/linux_kernel/
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

int buzzerExit(void)
{
    buzzerEnable(0);
	close(fdEnable);
	close(fdFrequency);
}

int buzzerPlaySong(int scale) // C:0, C#:1, ... , A:9, A#:10, B:11
{
    setFrequency(musicScale[scale]);
    buzzerEnable(1);
}

int buzzerStopSong(void)
{
    buzzerEnable(0);
}

