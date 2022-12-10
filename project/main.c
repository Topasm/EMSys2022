//최종 프로젝트 파일
#include "main.h"

static pthread_t ServerTh_id;

void PE_init()
{
    ball = generate_ball(60.0, 0.0);
    // mari_obj = generate_character(10, 300);
    // maru_obj = generate_character(20, 10);
}



static void *Server_thread(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    server_init();
    char buffers[100];

    // Reading the Message sent from Server
    value_Read = read(new_socket, buffers, 100);
    // printf ("Message from Client: %s \n", buffer); //버퍼에 클라이언트 메세지 쓰여있음
    while (1)
    {
        printf("Message from Client: %s \n", buffers); //버퍼에 클라이언트 메세지 쓰여있음

        send(new_socket, strCmd, strlen(strCmd), 0);
        printf("Message from Server is Sent to client\n");
    } // closing the connected socket
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
    pthread_create(&ServerTh_id,NULL, Server_thread,NULL);
    
    // client_init();
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
        // calculatePose(mari_obj, 1);
        //  int contact = CheckCollisionAnB(ball, mari_obj);
        //  if (contact == 1)
        //  {
        //      CheckImpulseAnB(ball, mari_obj);
        //      contact = 0;
        //  }
        ContactGround(ball, 1);
        // ContactGround(mari_obj, 0.8);
        update_ball((int)ball->pos.x, (int)ball->pos.y);
        update_screen();
        // printf("ball pose x = %f y = %f contact = %d\n", ball->pos.x, ball->pos.y, contact);
        // printf("---mari_obj pose x = %f y = %f contact = %d\n", mari_obj->pos.x, mari_obj->pos.y, contact);
    }

    fb_close();
    close(new_socket);

    // closing the listening socket
    shutdown(server_file_desc, SHUT_RDWR);
/////////////////////////////////////////////////////////////이 아래로 클라이언트
    send(sock, strCmd, strlen(strCmd), 0);
    // send message to socket server using send method
    printf("Message from Client Successfully Sent\n");
    while (1)
    {

        value_Read = read(sock, strCmd, 100);
        printf("Response from Server: %s\n", strCmd);
    }

    close(client_file_descriptor);
    return 0;
}



