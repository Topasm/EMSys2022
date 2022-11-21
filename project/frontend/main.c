#include <stdio.h>      //sprintf
#include <stdlib.h>     //atio

#include "GUI_FrameBuffer.h"

int main(int argc, char** argv)
{
	int fb_num;
	char fb_path[32];
	if (argc >= 2)
	{
		fb_num = atoi(argv[1]);
		sprintf(fb_path, "/dev/fb%d", fb_num);
	}
	else
	{
		sprintf(fb_path, "/dev/fb");
	}

    GUI_FB_Open(fb_path);
    GUI_FB_Close();

    return 0;
}