//최종 프로젝트 파일

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "device/driver.h"
#include "frontend/display/move_left.h"
#include "frontend/display/menu.h"
#include "device/libs/button.h"
#include "device/libs/led.h"
#include "device/libs/gyro.h"
#include "frontend/display/select_player_btn.h"
<<<<<<< HEAD
#include "device/libs/textlcd.h"
pthread_t th1, th2;
=======
pthread_t thmove, thled;
>>>>>>> 01fbbe33c5ff4890b4d08ecd1b00f4a9ad4b9dd5
pthread_mutex_t lock;



void* moveth(void* arg)
{   
	move_left();
}

void* ledth (void)
{
	led();
}


//===============================================================================================================
//main
//===============================================================================================================
int main(int argc, char **argv)
{

	int screen_width;
	int screen_height;
	int bits_per_pixel;
	int line_length;
    PLAYER=0;
	/*FrameBuffer init*/
	if (fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0)
	{
		printf("FrameBuffer Init Failed\r\n");
		return 0;
	}
	
   // pthread_create(&, NULL, ClientThFunc, (void *)&sock);
	/*clear FB.*/
	fb_clear();
	png_init();
	//int i = 0;
    dispaly_menu();
	select_player();
	//led fin
	//move_left();
	pthread_create(&thmove,NULL, moveth,NULL);
	pthread_create(&thled, NULL, ledth, NULL);

	while(1)
	{
		;
	}
    fb_close();
	return 0;
}

<<<<<<< HEAD
unsigned int linenum = 0;
stTextLCD stlcd;

static pthread_t textlcdTh_id;

int textlcd_Init(int linenum, char *str){
  
	const char* str1 = "player Win!";
	const char* str2 = "You are Winner!";
	txtlcd_Init();
	lcdtextwrite(str1, str2,1);
	sleep(1);
	lcdtextwrite(str1, str2,2);
	txtlcd_off();
	txtlcd_Init();
	sleep(1);
	lcdtextwrite(str1, str2,0);
}
=======



>>>>>>> 01fbbe33c5ff4890b4d08ecd1b00f4a9ad4b9dd5
