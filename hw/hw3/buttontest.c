#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl

// first read input device
#define  INPUT_DEVICE_LIST	"/dev/input/event"
//실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices"
//PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일

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

int main(int argc, char *argv[])
{
	int    fp;
	int		readSize,inputIndex;
	struct input_event  stEvent;
	fp = open(INPUT_DEVICE_LIST, O_RDONLY);
	
	while(1)
	{
		readSize = read(fp, &stEvent , sizeof(stEvent));
		if (readSize != sizeof(stEvent))
		{
			continue;
		}

		if ( stEvent.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP:	printf("Volume up key):");	break;
				case KEY_HOME:		printf("Home key):");		break;
				case KEY_SEARCH:	printf("Search key):");		break;
				case KEY_BACK:		printf("Back key):");		break;
				case KEY_MENU:		printf("Menu key):");		break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
			if ( stEvent.value )	printf("pressed\n");
			else					printf("released\n");
		}
		else //EV_SYN
		{
			// do notthing
		}
	}
	close(fp);		
}