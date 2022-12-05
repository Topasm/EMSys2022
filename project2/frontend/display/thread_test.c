#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../libfbdev/libfbdev.h"
#include "../lodepng/lodepng.h"
#include "../../device/gyro.h"

char *bg_data;
char *mari_data;
char *maru_data;
char *menu_data;

unsigned int error;
const char *bg_path = "../source/background.png";
const char *mari_path = "../source/mari.png";
const char *maru_path = "../source/mari.png"; //maru 로 변경 해야 함
const char *menu_path = "../source/menu.png";

int cols_bg = 0, rows_bg = 0;
int cols_mari = 0, rows_mari = 0;
int cols_maru = 0, rows_maru = 0;
int cols_menu = 0, rows_menu = 0;


void png_init()
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
	error = lodepng_decode32_file(&menu_data, &cols_menu, &rows_menu, menu_path);
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
}
void update_menu(void)
{
	picture_in_position(menu_data, cols_menu, rows_menu,0,0);
}


//player 변수
int player = 1; //1p or 2p

int move_left(void)
{	
	int x1=0, x2=400;
	int dx1=0, dx2=0;
	while (1)
	{
		
		update_background();
		update_mari(x1,200);
		update_screen();

        if
		if(x1>=240)	
		{
			printf("saturation\n");
			dx1=get_dx();
			if(dx1>0)
				x1=x1-dx1;
			else
				x1=295;
		}		
		else if(x1<=0)
		{
			printf("saturation\n");
			dx1=get_dx();
			if(dx1<0)
				x1=x1-dx1;
			else
				x1=0;
		}
        else if(x2<=300)
        {
            printf("maru saturation\n");
            dx2=get_dx();
            if(dx2>0)
                x2=x2-dx2;
            else
                dx=300;
        }
        else if(x2>=550)
        {
            printf("maru saturation\n");
            dx1=get_dx();
			if(dx2<0)
				x2=x2-dx2;
			else
				x2=0;
        }
		else if(x1)
		{
			printf("%d\n",x1);
			dx1=get_dx();
			x1=x1-dx1;
			printf("%d, %d\n",x1,dx1);
		}
	}
	fb_close();
	return 0;
}



