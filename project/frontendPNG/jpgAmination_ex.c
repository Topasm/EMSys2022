#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libfbdev/libfbdev.h"
#include "lodepng/lodepng.h"



int main(int argc, char **argv)
{
	unsigned int error;

	int screen_width;
	int screen_height;
	int bits_per_pixel;
	int line_length;
	int cols = 0, rows = 0;
	char *data1;
	char *data2;
	
	/*FrameBuffer init*/
	if (fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0)
	{
		printf("FrameBuffer Init Failed\r\n");
		return 0;
	}

	/*clear FB.*/
	fb_clear();

		/*FrameBuffer init*/


	char filename[200] = {
		0,
	};
	snprintf(filename, 200, "./source/background.png");
	
	char filename2[200] = {
		0,
	};
	snprintf(filename2, 200, "./source/mari.png");
	
	error = lodepng_decode32_file(&data1, &cols, &rows, filename);
	printf("rows: %d cols: %d\n", rows,cols);
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
	fb_write_reverse(data1, cols, rows);
	error = lodepng_decode32_file(&data2, &cols, &rows, filename2);
	printf("rows: %d cols: %d", rows,cols);
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

	



	fb_write_reverse2(data2, cols, rows, 100,10);//이동 구현
	free(data1);

	fb_close();
	fb_close2();
	return 0;
}
