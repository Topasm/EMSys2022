#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "drawLCD.h"
#include "../lodepng/lodepng.h"

char *bg_data;
char *mari_data;
char *maru_data;
char *menu_data;

unsigned int error;
const char *bg_path = "./source/background.png";
const char *mari_path = "./source/mari.png";
const char *maru_path = "./source/mari.png"; //maru 로 변경 해야 함
const char *menu_path = "./source/menu.png";

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



