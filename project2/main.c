//최종 프로젝트 파일

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
#include "driver.h"
#include "move_left.h"
#include "menu.h"

int main(int argc, char **argv)
{

	int screen_width;
	int screen_height;
	int bits_per_pixel;
	int line_length;

	/*FrameBuffer init*/
	if (fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0)
	{
		printf("FrameBuffer Init Failed\r\n");
		return 0;
	}
	/*clear FB.*/
	fb_clear();
	png_init();
	//int i = 0;
    dispaly_menu();
	move_left();
	
    fb_close();
	return 0;
}