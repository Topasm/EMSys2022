#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "frontend/libfbdev/libfbdev.h"
#include "frontend/lodepng/lodepng.h"
#include "device/gyro.h"
#include "frontend/frontend.h"

int dispaly_menu(void)
{	
	while (1)
	{
		
		update_menu();
		update_screen();
	}
	fb_close();
	return 0;
}
