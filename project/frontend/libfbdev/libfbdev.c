
#include "libfbdev.h"
static unsigned long sbuffer[1280*800];	//스크린 버퍼





int fb_init(int * screen_width, int * screen_height, int * bits_per_pixel, int * line_length)
{
	
    struct  fb_fix_screeninfo fbfix;

	if( (fbfd0 = open(FBDEV_FILE0, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE0);
        return -1;
    }

    if( ioctl(fbfd0, FBIOGET_VSCREENINFO, &fbInfo) )
    {
        printf("%s: ioctl error - FBIOGET_VSCREENINFO \n", FBDEV_FILE0);
		close(fbfd0);
        return -1;
    }
   	if( ioctl(fbfd0, FBIOGET_FSCREENINFO, &fbFixInfo) )
    {
        printf("%s: ioctl error - FBIOGET_FSCREENINFO \n", FBDEV_FILE0);
        close(fbfd0);
        return -1;
    }
	//printf ("FBInfo.YOffset:%d\r\n",fbInfo.yoffset);
	fbInfo.yoffset = 0;
	ioctl(fbfd0, FBIOPUT_VSCREENINFO, &fbInfo);	//슉!
    if (fbInfo.bits_per_pixel != 32)
    {
        printf("bpp is not 32\n");
		close(fbfd0);
        return -1;
    }	

    fbWidth = *screen_width    =   fbInfo.xres;
    fbHeight = *screen_height   =   fbInfo.yres;
    *bits_per_pixel  =   fbInfo.bits_per_pixel;
    *line_length     =   fbFixInfo.line_length;

	pfbmap  =   (unsigned long *)
        mmap(0, PFBSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd0, 0);

	
	if ((unsigned)pfbmap == (unsigned)-1)
    {
        printf("fbdev mmap failed\n");
        close(fbfd0);
		return -1;
    }
	#ifdef ENABLED_DOUBLE_BUFFERING
		currentEmptyBufferPos = DOUBLE_BUFF_START;	//더블버퍼링 임시 주소로 할당
	#else
		currentEmptyBufferPos = 0;
	#endif
	//printf ("CurrentEmptyBuffPos:%d\r\n",currentEmptyBufferPos);
	return 1;
}

void fb_clear(void)
{
	int coor_y = 0;
	int coor_x = 0;
	// fb clear - black
    for(coor_y = 0; coor_y < fbHeight; coor_y++) 
	{
        unsigned long *ptr =   pfbmap + currentEmptyBufferPos + (fbWidth * coor_y);
        for(coor_x = 0; coor_x < fbWidth; coor_x++)
        {
            *ptr++  =   0x000000;
        }
    }
	
	#ifdef ENABLED_DOUBLE_BUFFERING
		fb_doubleBufSwap();
	#endif
}


void fb_doubleBufSwap(void)
{
	if (currentEmptyBufferPos == 0)
	{
		fbInfo.yoffset = 0;
		currentEmptyBufferPos = DOUBLE_BUFF_START;
	}
	else
	{
		fbInfo.yoffset = fbHeight;
		currentEmptyBufferPos = 0;		
	}
	ioctl(fbfd0, FBIOPUT_VSCREENINFO, &fbInfo);	//슉!
}

void fb_close(void)
{
	printf ("Memory UnMapped!\r\n");
    munmap( pfbmap, PFBSIZE);
	printf ("CloseFB\r\n");
    close( fbfd0);
}

void picture_in_position(char* picData, int picWidth, int picHeight, int posx, int posy)//포지션에 따라 이미지 출력하는 함수수
{
	int coor_y=0;
	int coor_x=0;
	int targetHeight = (fbHeight<picHeight)?fbHeight:picHeight;	//if Screen과 파일 사이즈가 안맞으면
	int targetWidth = (fbWidth<picWidth)?fbWidth:picWidth;		//if Screen과 파일 사이즈가 안맞으면
	
	for(coor_y = 0; coor_y < targetHeight; coor_y++) 
	{
		int bmpYOffset = coor_y*picWidth*4; ///Every 1Pixel requires 4Bytes.
		int bmpXOffset = 0;
		for (coor_x=0; coor_x < targetWidth; coor_x++)
		{
			//BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
			if(((unsigned long)(picData[bmpYOffset+bmpXOffset+3])) == 0)
			{
				bmpXOffset+=4;	//4 Byte. 투명도 검출 0이면 업데이트 안함
			}
			else{
			sbuffer[coor_y*fbWidth + posx + fbWidth*posy + (coor_x) + currentEmptyBufferPos] = 
				((unsigned long)(picData[bmpYOffset+bmpXOffset+0])<<16) 	+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8) 		+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+2]));
				bmpXOffset+=4;	//4 Byte.
			}
		}
    }	
	#ifdef ENABLED_DOUBLE_BUFFERING
	
		fb_doubleBufSwap();
	#endif	
}



void update_screen(void)
{
	memcpy(pfbmap,sbuffer,sizeof(sbuffer));
}




void picture_in_position_rotation(char* picData, int picWidth, int picHeight, int posx, int posy, double rad)//포지션에 따라 이미지 출력하는 함수수
{
	int coor_y=0;
	int coor_x=0;
	int targetHeight = (fbHeight<picHeight)?fbHeight:picHeight;	//if Screen과 파일 사이즈가 안맞으면
	int targetWidth = (fbWidth<picWidth)?fbWidth:picWidth;		//if Screen과 파일 사이즈가 안맞으면
	
	for(coor_y = 0; coor_y < targetHeight; coor_y++) 
	{
		int bmpYOffset = coor_y*picWidth*4; ///Every 1Pixel requires 4Bytes.
		int bmpXOffset = 0;
		for (coor_x=0; coor_x < targetWidth; coor_x++)
		{
			//BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
			if(((unsigned long)(picData[bmpYOffset+bmpXOffset+3])) == 0)
			{
				bmpXOffset+=4;	//4 Byte. 투명도 검출 0이면 업데이트 안함
			}
			else{
			pfbmap[coor_y*fbWidth + posx + fbWidth*posy + (coor_x) + currentEmptyBufferPos] = 
				((unsigned long)(picData[bmpYOffset+bmpXOffset+0])<<16) 	+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8) 		+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+2]));
				bmpXOffset+=4;	//4 Byte.
			}
		}
    }	
	#ifdef ENABLED_DOUBLE_BUFFERING
	
		fb_doubleBufSwap();
	#endif	
}


