#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libfbdev/libfbdev.h"
#include "../lodepng/lodepng.h"
#include "../../device/libs/gyro.h"
#include "drawLCD.h"

// player 변수
int x1 = 0, x2 = 520;

int check(int dx1, int dx2)
{

	while (1)
	{
		// 1p: player==1
		update_background();
		update_mari(x1, 200);
		update_maru(x2, 200);
		update_screen();

		// mari
		if (x1 >= 240) // not to over net
		{
			printf("mari saturation\n");
			if (dx1 > 0)
				x1 = x1 - dx1;
			else
				x1 = 295;
		}

		else if (x1 <= 0) // not to over left wall
		{
			printf("mari saturation\n");
			if (dx1 < 0)
				x1 = x1 - dx1;
			else
				x1 = 0;
		}

		else // normal
		{
			printf("%d\n", x1);
			x1 = x1 - dx1;
			printf("%d, %d\n", x1, dx1);
		}

		// maru
		if (x2 <= 520) // not to over net
		{
			printf("maru saturation\n");
			if (dx2 < 0)
				x2 = x2 - dx2;
			else
				dx2 = 520;
		}

		else if (x2 >= 830) // not to over right wall
		{
			printf("maru saturation\n");
			if (dx2 > 0)
				x2 = x2 - dx2;
			else
				x2 = 830;
		}

		else // normal
		{
			printf("%d\n", x1);
			x2 = x2 - dx2;
			printf("%d, %d\n", x2, dx2);
		}
	}
	fb_close();
	return 0;
}
