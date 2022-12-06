//최종 프로젝트 파일

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "device/driver.h"
#include "frontend/display/move_left.h"
#include "frontend/display/menu.h"
#include "device/libs/button.h"
#include "backend/PEobject.h"
#include "backend/PEcollide.h"
#include "backend/PEworld.h"
#include "device/libs/gyro.h"

object *ball;
object *mari_obj;
object *maru_obj;

void PE_init()
{
    ball = generate_ball(60.0, 0.0);
    //mari_obj = generate_character(10, 300);
    //maru_obj = generate_character(20, 10);
}

int main(int argc, char **argv)
{

    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;

    /*FrameBuffer init*/
    if (fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0)
    {
        printf("FrameBuffer Init Failed\r\n");
        return 0;
    }
    /*clear FB.*/
    fb_clear();
    png_init();
    PE_init();
    // int i = 0;
     dispaly_menu();

    // // button start
    // int msgID = buttonInit();
    // printf("buttonInit . . .\n");

    // BUTTON_MSG_T buttonMsg;
    // int recievedVal = 0;

    // /**/ while (1)
    // {
    //     recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, IPC_NOWAIT);
    //     if (recievedVal == -1)
    //     {
    //         printf("failed");
    //         break;
    //     }
    // }

    // while (1)
    // {
    //     recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
    //     if (recievedVal < 0)
    //     {
    //         printf("error");
    //     }

    //     switch (buttonMsg.keyInput)
    //     {
    //     case KEY_VOLUMEUP:
    //         printf("Volume up key):");
    //         break;
    //     case KEY_HOME:
    //         printf("Home key):");
    //         break;
    //     case KEY_SEARCH:
    //         printf("Search key):");
    //         break;
    //     case KEY_BACK:
    //         printf("Back key):");
    //         break;
    //     case KEY_MENU:
    //         printf("Menu key):");
    //         break;
    //     case KEY_VOLUMEDOWN:
    //         printf("Volume down key):");
    //         break;
    //     }

    //     if (buttonMsg.pressed)
    //     {
    //         printf("pressed\n");
    //     }
    //     else
    //     {
    //         printf("released\n");
    //     }
    // }
    // buttonExit();
    // // button fin

    // sleep(3);

    // // player 변수
    // int player = 1; // 1p or 2p
    // int x1 = 0, x2 = 520;
    // int dx1 = 0, dx2 = 0; //하나는 본인 키트에서 dx 받기 / 하나는 상대방 키트의 dx.

    // while (1)
    // {
    //     // 1p: player==1
    //     if (player == 1)
    //     {
    //         update_background();
    //         update_mari(x1, 200);
    //         update_maru(x2, 200);
    //         update_screen();

    //         // mari
    //         if (x1 >= 240) // not to over net
    //         {
    //             printf("mari saturation\n");
    //             dx1 = get_dx();
    //             if (dx1 > 0)
    //                 x1 = x1 - dx1;
    //             else
    //                 x1 = 295;
    //         }

    //         else if (x1 <= 0) // not to over left wall
    //         {
    //             printf("mari saturation\n");
    //             dx1 = get_dx();
    //             if (dx1 < 0)
    //                 x1 = x1 - dx1;
    //             else
    //                 x1 = 0;
    //         }

    //         else // normal
    //         {
    //             printf("%d\n", x1);
    //             dx1 = get_dx();
    //             x1 = x1 - dx1;
    //             printf("%d, %d\n", x1, dx1);
    //         }

    //         // maru
    //         if (x2 <= 520) // not to over net
    //         {
    //             printf("maru saturation\n");
    //             dx2 = get_dx();
    //             if (dx2 < 0)
    //                 x2 = x2 - dx2;
    //             else
    //                 dx2 = 520;
    //         }

    //         else if (x2 >= 830) // not to over right wall
    //         {
    //             printf("maru saturation\n");
    //             dx2 = get_dx();
    //             if (dx2 > 0)
    //                 x2 = x2 - dx2;
    //             else
    //                 x2 = 830;
    //         }

    //         else // normal
    //         {
    //             printf("%d\n", x1);
    //             dx2 = get_dx();
    //             x2 = x2 - dx2;
    //             printf("%d, %d\n", x2, dx2);
    //         }
    //     }

    while (1)
    {
        update_background();
        calculatePose(ball, 1.8);
        //calculatePose(mari_obj, 1);
        // int contact = CheckCollisionAnB(ball, mari_obj);
        // if (contact == 1)
        // {
        //     CheckImpulseAnB(ball, mari_obj);
        //     contact = 0;
        // }
        ContactGround(ball, 1);
        //ContactGround(mari_obj, 0.8);
        update_ball((int)ball->pos.x, (int)ball->pos.y);
        update_screen();
        // printf("ball pose x = %f y = %f contact = %d\n", ball->pos.x, ball->pos.y, contact);
        // printf("---mari_obj pose x = %f y = %f contact = %d\n", mari_obj->pos.x, mari_obj->pos.y, contact);
    }

    fb_close();
    return 0;
}