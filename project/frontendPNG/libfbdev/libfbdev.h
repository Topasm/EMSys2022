#ifndef _LIB_FBDEV_H_
#define _LIB_FBDEV_H_
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/mman.h>
#include <linux/fb.h>   // for fb_var_screeninfo, FBIOGET_VSCREENINFO
#define FBDEV_FILE0 "/dev/fb0"


static int fbfd0;
static int fbHeight=0;	//현재 하드웨어의 사이즈
static int fbWidth=0;	//현재 하드웨어의 사이즈
static unsigned long   *pfbmap;	//프레임 버퍼
static struct fb_var_screeninfo fbInfo;	//To use to do double buffering.
static struct fb_fix_screeninfo fbFixInfo;	//To use to do double buffering.


#define PFBSIZE 			(fbHeight*fbWidth*sizeof(unsigned long)*2)	//Double Buffering
#define DOUBLE_BUFF_START	(fbHeight*fbWidth)	///Double Swaping
static int currentEmptyBufferPos = 0;
//1 Pixel 4Byte Framebuffer.



// typedef struct image{
//     int rows;
//     int cols;
//     char *data;
// }


int fb_init(int * screen_width, int * screen_height, int * bits_per_pixel, int * line_length);
void fb_close(void);
void fb_clear(void);
void picture_in_position_rotation(char* picData, int picWidth, int picHeight, int posx, int posy, double rad);
void picture_in_position(char* picData, int picWidth, int picHeight, int posx, int posy);
void update_screen(void);
void fb_doubleBufSwap(void);
#endif