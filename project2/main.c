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
#include "device/driver.h"
#include "frontend/display/move_left.h"
#include "frontend/display/menu.h"
#include "device/libs/button.h"


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


	// button start
	int msgID = buttonInit();
    printf("buttonInit . . .\n");

    BUTTON_MSG_T buttonMsg;
    int recievedVal = 0;

    /**/ while (1)
    {
        recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, IPC_NOWAIT);
        if (recievedVal == -1)
        {
            printf("failed");
			break;
        }
    } 

    while (1)
    {
        recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
        if (recievedVal < 0)
        {
            printf("error");
        }

        switch (buttonMsg.keyInput)
        {
        case KEY_VOLUMEUP:
            printf("Volume up key):");
            break;
        case KEY_HOME:
            printf("Home key):");
            break;
        case KEY_SEARCH:
            printf("Search key):");
            break;
        case KEY_BACK:
            printf("Back key):");
            break;
        case KEY_MENU:
            printf("Menu key):");
            break;
        case KEY_VOLUMEDOWN:
            printf("Volume down key):");
            break;
        }

        if (buttonMsg.pressed)
        {
            printf("pressed\n");
        }
        else
        {
            printf("released\n");
        }
    }
    buttonExit();
	//button fin


	sleep(3);
	move_left();
	
    fb_close();
	return 0;
}