#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>    //open, close 위해
#include <fcntl.h>     //for O_RDWR
#include <sys/ioctl.h> //for ioctl
#include <pthread.h>
#include "drawLCD.h"
//#include "../lodepng/lodepng.h"
#include "../../device/libs/gyro.h"
#include "../../device/libs/button.h"

static pthread_t buttonTh_id;

char *bg_data;
char *mari_data;
char *maru_data;
char *game_start_data;
char *player_data;

unsigned int error;
const char *bg_path = "./source/background.png";
const char *mari_path = "./source/mari.png";
const char *maru_path = "./source/mari.png"; // maru 로 변경 해야 함
const char *game_start_path = "./source/game_start.png";
const char *player_path = "./source/player.png";

int cols_bg = 0, rows_bg = 0;
int cols_mari = 0, rows_mari = 0;
int cols_maru = 0, rows_maru = 0;
int cols_game_start = 0, rows_game_start = 0;
int cols_player = 0, rows_player = 0;

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
    error = lodepng_decode32_file(&game_start_data, &cols_game_start, &rows_game_start, game_start_path);
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    error = lodepng_decode32_file(&player_data, &cols_player, &rows_player, player_path);
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
}

void update_background(void)
{
    picture_in_position(bg_data, cols_bg, rows_bg, 0, 0);
}
void update_mari(int posx, int posy)
{
    picture_in_position(mari_data, cols_mari, rows_mari, posx, posy);
}
void update_maru(int posx, int posy)
{
    picture_in_position(maru_data, cols_maru, rows_maru, posx, posy);
}
void update_player(void)
{
    picture_in_position(player_data, cols_player, rows_player, 0, 0);
}
void update_game_start(void)
{
    picture_in_position(game_start_data, cols_game_start, rows_game_start, 0, 0);
}

static const unsigned int keyCodeConv[KEY_INDEX_MAX] =
    {
        KEY_HOME, // key 나열
        KEY_BACK,
        KEY_SEARCH,
        KEY_MENU,
        KEY_VOLUMEUP,
        KEY_VOLUMEDOWN};
//프레임버퍼에 메뉴 사진 넣고 띄우기
while (1)
{
    switch (status)
    {
    case gamestart: // gamestart 화면 띄우기
        draw_bmp_game_start();
        printf("Press Back Key\r\n");
        writeLCD(1, "Press Back Key");
        writeLCD(2, "                ");
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, OFF);
        }
        returnValue = msgrcv(msgID, &messageRxData, sizeof(int), 0, 0); // 버튼 입력 받기
        if (returnValue < 0)
        {
            printf("Receive Key Failed\r\n");
            status = player;
            break;
        }
        if (messageRxData.keyInput == KEY_BACK)
        {
            status = player;
        }
    case player: // player선택 화면 띄우기
        draw_bmp_player();
        printf("Choose the Player\r\n");
        writeLCD(1, "Choose the Player!");
        writeLCD(2, "Search or Menu Key!");
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, OFF);
        }
        returnValue = msgrcv(msgID, &messageRxData, sizeof(int), 0, 0); // 버튼 입력 받기
        if (returnValue < 0)
        {
            printf("Receive Key Failed\r\n");
            status = player;
            break;
        }
        switch (messageRxData.keyInput)
        {
        case KEY_SEARCH: // Player1모드
            printf("Player1\r\n");
            printf("PLAY key\r\n");
            status = Player1;
            break;
        case KEY_MENU: // Player2모드
            printf("Player2\r\n");
            printf("PLAY key\r\n");
            status = Player2;
            break;
        default: // 잘못된 키 입력
            printf("KEY INPUT ERROR \r\n");
            break;
        }
        break;

    case win1: // player1 게임 승리
        // 프레임버퍼에 player1 승리 사진 밀어넣고 띄우기
        writeLCD(1, "Player1  Winner!");
        writeLCD(2, "                ");
        draw_bmp_win1();
        pthread_cancel(thread);
        returnValue = msgrcv(msgID, &messageRxData, sizeof(int), 0, 0); // 버튼 입력 받기
        if (returnValue < 0)
        {
            printf("Receive Key Failed\r\n");
            status = WIN;
            break;
        }
        if (messageRxData.keyInput == KEY_BACK)
        {
            status = player;
        }
        else if (messageRxData.keyInput == KEY_VOLUMEUP)
        {
            status = EXIT;
        }
        break;

    case win2: // player2 게임 승리
        // 프레임버퍼에 player2 승리 사진 밀어넣고 띄우기
        writeLCD(1, "Player2  Winner!");
        writeLCD(2, "                ");
        draw_bmp_win2();
        pthread_cancel(thread);
        returnValue = msgrcv(msgID, &messageRxData, sizeof(int), 0, 0); // 버튼 입력 받기
        if (returnValue < 0)
        {
            printf("Receive Key Failed\r\n");
            status = WIN;
            break;
        }
        if (messageRxData.keyInput == KEY_BACK)
        {
            status = player;
        }
        else if (messageRxData.keyInput == KEY_VOLUMEUP)
        {
            status = EXIT;
        }
        break;

    case EXIT: // 게임 종료
        writeLCD(1, "game over");
        writeLCD(2, "                ");
        draw_background(0x000000, 0);
        buttonExit();
        return 0;
