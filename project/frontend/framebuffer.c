#include <stdio.h>      //printf
#include <stdlib.h>     //malloc
#include <unistd.h>     //open,close
#include <fcntl.h>      //O_RDWR
#include <sys/ioctl.h>  //ioctl
#include <sys/mman.h>   //mmap,PROT_
#include <linux/fb.h>   //fb_var_screeninfo,fb_fix_screeninfo

#include "GUI_Type.h"
#include "GUI_FrameBuffer.h"

///////////////////////////////////////////////////////////////////////
// external variable
///////////////////////////////////////////////////////////////////////
GUI_FB_t *g_fb;          // frame buff

///////////////////////////////////////////////////////////////////////
// external function
///////////////////////////////////////////////////////////////////////
int GUI_FB_Open(const char *fb_path)
{
    struct fb_var_screeninfo var;   // variable information of frame
    struct fb_fix_screeninfo fix;   // fixed information of frame

    g_fb = (GUI_FB_t *)malloc(sizeof(GUI_FB_t));

    // access
    if ( access( fb_path, F_OK ) )
    {
        printf("Can't access %s\n", fb_path);
        return 0;
    }
    // open
    if ( 0 > (g_fb->fd = open( fb_path, O_RDWR )) )
    {
        printf("%s permission denied\n", fb_path);
        return 0;
    }
    // io control var info
    if ( ioctl( g_fb->fd, FBIOGET_VSCREENINFO, &var) )
    {
        printf("can't execute FBIOGET_VSCREENINFO\n");
        return 0;
    }
    // io control fix info
    if ( ioctl( g_fb->fd, FBIOGET_FSCREENINFO, &fix) )
    {
        printf("can't execute FBIOGET_FSCREENINFO\n");
        return 0;
    }

    g_fb->screen_width      = var.xres;                    // screen width pixel
    g_fb->screen_height     = var.yres;                    // screen height pixel
    g_fb->bits_per_pixel    = var.bits_per_pixel;          // bits per pixel
    g_fb->line_length       = fix.line_length;             // bytes per line

    g_fb->mem_size          = g_fb->line_length * g_fb->screen_height; // memory size
    g_fb->red_offset        = var.red.offset;   // red offset
    g_fb->green_offset      = var.green.offset; // green offset
    g_fb->blue_offset       = var.blue.offset;  // blue offset

#if 1
    printf( "*********************************************************\n");
    printf( "** FRAME BUFFER INFO                                   **\n");
    printf( "*********************************************************\n");
    printf( "frame buff open (%s)\n", fb_path);
    printf( "screen width   = %d\n", g_fb->screen_width  );
    printf( "screen height  = %d\n", g_fb->screen_height );
    printf( "bits per pixel = %d\n", g_fb->bits_per_pixel);
    printf( "line length    = %d\n", g_fb->line_length   );
    printf( "memory size    = %d\n", g_fb->mem_size      );
#endif

    return 1;
}

int GUI_FB_Close(void)
{
    if (g_fb == NULL)
    {
        return 0;
    }

    free(g_fb);
    g_fb = NULL;

    return 1;
}
