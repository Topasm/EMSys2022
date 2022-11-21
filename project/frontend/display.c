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





//게임 시작 화면 출력

//버튼으로 게임 player1 or 2 선택
//캐릭터 구현(마리 마루 캐릭터 생성)




//자이로스코프 센서 기울기에 따라 캐릭터 좌 우 이동


//승/패를 알려주는 창


//게임 종료






