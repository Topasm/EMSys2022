#include "display.h"

int fb_fd0;
int fb_fd1;
struct fb_var_screeninfo fbvar;
struct fb_fix_screeninfo fbfix;
unsigned char *fb_mapped0;
unsigned char *fb_mapped1;
unsigned long *ptr0;
unsigned long *ptr1;

int screen_width;
int screen_height;
int bits_per_pixel;
int line_length;

int mem_size;

    char *pData, *data;
    char r, g, b;
    unsigned long pixel;
    int cols = 0, rows = 0;
    unsigned long bmpdata[1280 * 800];
    int k, t;
    unsigned char *pfbmap;

int display_init(void)
{
    // 커서 제거
    int conFD = open("/dev/tty0", O_RDWR);
    ioctl(conFD, KDSETMODE, KD_GRAPHICS);
    close(conFD);

    if (access(FBDEV_FILE0, F_OK))
    {
        printf("%s: access error\n", FBDEV_FILE0);
        exit(1);
    }

    if ((fb_fd0 = open(FBDEV_FILE0, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE0);
        exit(1);
    }

    if (ioctl(fb_fd0, FBIOGET_VSCREENINFO, &fbvar))
    {
        printf("%s: ioctl error - FBIOGET_VSCREENINFO \n", FBDEV_FILE0);
        exit(1);
    }

    if (ioctl(fb_fd0, FBIOGET_FSCREENINFO, &fbfix))
    {
        printf("%s: ioctl error - FBIOGET_FSCREENINFO \n", FBDEV_FILE0);
        exit(1);
    }

    if (access(FBDEV_FILE1, F_OK))
    {
        printf("%s: access error\n", FBDEV_FILE1);
        exit(1);
    }

    if ((fb_fd1 = open(FBDEV_FILE1, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE1);
        exit(1);
    }

    if (ioctl(fb_fd1, FBIOGET_VSCREENINFO, &fbvar))
    {
        printf("%s: ioctl error - FBIOGET_VSCREENINFO \n", FBDEV_FILE1);
        exit(1);
    }

    if (ioctl(fb_fd1, FBIOGET_FSCREENINFO, &fbfix))
    {
        printf("%s: ioctl error - FBIOGET_FSCREENINFO \n", FBDEV_FILE1);
        exit(1);
    }

    screen_width = fbvar.xres;
    screen_height = fbvar.yres;
    bits_per_pixel = fbvar.bits_per_pixel;
    line_length = fbfix.line_length;

    printf("screen_width : %d\n", screen_width);
    printf("screen_height : %d\n", screen_height);
    printf("bits_per_pixel : %d\n", bits_per_pixel);
    printf("line_length : %d\n", line_length);

    mem_size = screen_width * screen_height * 4;
    fb_mapped0 = (unsigned char *)mmap(0, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd0, 0);
    fb_mapped1 = (unsigned char *)mmap(0, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd1, 0);

    if (fb_mapped0 < 0 || fb_mapped1 < 0)
    {
        printf("mmap error!\n");
        exit(1);
    }

    return 0;
}



//게임 시작 화면 출력






//버튼으로 게임 player1 or 2 선택
//캐릭터 구현(마리 마루 캐릭터 생성)




//자이로스코프 센서 기울기에 따라 캐릭터 좌 우 이동


//승/패를 알려주는 창


//게임 종료






