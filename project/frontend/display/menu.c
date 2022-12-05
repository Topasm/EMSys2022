#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "drawLCD.h"
#include "../lodepng/lodepng.h"


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
