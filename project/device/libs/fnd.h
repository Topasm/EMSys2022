//write시 사용하는 데이터 구조체 정의
#ifndef __FND_DRV_H__
#define __FND_DRV_H__
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
int fndDisp(int num , int dotflag);
void fnddoHelp(void);
int fndOff();

// 구조체 형식
typedef struct FNDWriteDataForm_tag
{
    //6개의 FND Array에 표시 될 숫자가 들어감
    char DataNumeric[FND_DATA_BUFF_LEN];
    //점의 점등 유무 표시
    char DataDot[FND_DATA_BUFF_LEN];
    //각 DataNumeric의 데이터 Valid 표시
    char DataValid[FND_DATA_BUFF_LEN];
} stFndWriteForm, *pStFndWriteForm;

#endif // __FND_DRV_H__