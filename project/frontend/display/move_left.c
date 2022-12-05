#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libfbdev/libfbdev.h"
#include "../lodepng/lodepng.h"
#include "../../device/gyro.h"
#include "drawLCD.h"


//int x=100; 
//int flag_ForBack=1;

/* void png_init()
{
	error = lodepng_decode32_file(&bg_data, &cols_bg, &rows_bg, bg_path);
	if (error)
		printf("background error %u: %s\n", error, lodepng_error_text(error));
	
	error = lodepng_decode32_file(&mari_data, &cols_mari, &rows_mari, mari_path);
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	error = lodepng_decode32_file(&maru_data, &cols_maru, &rows_maru, maru_path);
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
}

void update_background(void)
{
	picture_in_position(bg_data, cols_bg, rows_bg,0,0);
}

void update_mari(int posx, int posy)
{
	picture_in_position(mari_data, cols_mari, rows_mari,posx,posy);
}
void update_maru(int posx, int posy)
{
	picture_in_position(maru_data, cols_maru, rows_maru,posx,posy);
} */




int move_left(void)
{	
	int x=0;
	int dx=0;
	while (1)
	{
		
		update_background();
		update_mari(x,200);
		update_screen();

		if(x>=240)	
		{
			printf("saturation\n");
			dx=get_dx();
			if(dx>0)
				x=x-dx;
			else
				x=295;
		}		
		else if(x<=0)
		{
			printf("saturation\n");
			dx=get_dx();
			if(dx<0)
				x=x-dx;
			else
				x=0;
		}
		else
		{
			printf("%d\n",x);
			dx=get_dx();
			x=x-dx;
			printf("%d, %d\n",x,dx);
		}
	}
	fb_close();
	return 0;
}
