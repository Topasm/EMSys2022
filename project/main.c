// 최종 프로젝트 파일

#include "main.h"

typedef struct server2client
{
    int ball_x;
    int ball_y;
    int mari_x;
    int mari_y;
    int maru_x;
    int maru_y;
    int score; // 기본 0 1 이면 1번 승 2면 2번승
} s2c;
s2c s2c2;
// struct server2client *s2c;

typedef struct client2server
{
    int whichChar; // 어떤 캐릭터 선택
    int gyrodata;
} c2s;
// struct client2server *c2s;
c2s c2s2;
// char buffers[100];

static pthread_t ServerTh_id;

void PE_init()
{
    ball = generate_ball(60.0, 0.0);
    // mari_obj = generate_character(10, 300);
    // maru_obj = generate_character(20, 10);
}

static pthread_t rcv_thread;
int sock = 0;
int new_socket = 0;
static void *ClientThFunc(void)
{
    sock = client_init();

    // value_Read = recv(sock, (struct server2client *)&s2c, sizeof(s2c), 0);
    // send message to socket server using send method
    printf("Message from Client Successfully Sent\n");
    while (1)
    {
        // value_Read = read(sock, strCmd, 100);

        value_Read = recv(new_socket, (struct server2client*)&s2c2, sizeof(s2c2), 0);
        printf("%d \n", s2c2.ball_x);
        printf("%d \n", s2c2.ball_y);
        printf("%d \n", s2c2.mari_x);
        printf("%d \n", s2c2.mari_y);
        printf("%d \n", s2c2.maru_x);
        printf("%d \n", s2c2.maru_y);
        printf("%d \n", s2c2.score);
        send(sock, (struct client2server*)&c2s2, sizeof(c2s2), 0);
    }
}

static void *Server_thread(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    new_socket = server_init();

    while (1)
    {
        send(new_socket, (struct server2client*)&s2c2, sizeof(s2c2), 0);
        value_Read = recv(sock, (struct client2server*)&c2s2, sizeof(c2s2), 0);
        // printf("Message from Client: %s \n", buffers); // 버퍼에 클라이언트 메세지 쓰여있음

        printf("%d \n", c2s2.whichChar);
        printf("%d \n", c2s2.gyrodata);

        // printf("Message from Server is Sent to client\n");
    } // closing the connected socket
}

int main(int argc, char **argv)
{
    // int sd;
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
    // server_init();
    pthread_create(&rcv_thread, NULL, ClientThFunc, (void *)&sock);

    // int i = 0;
    pthread_create(&ServerTh_id, NULL, Server_thread, NULL);

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

    // printf ("Message from Client: %s \n", buffer); //버퍼에 클라이언트 메세지 쓰여있음
    while (1)
    {

        // Reading the Message sent from Server
        // value_Read = recv(sd,(struct server2client *)&s2c, sizeof(s2c), 0);
        // printf("Message from Client: %s \n", buffers); //버퍼에 클라이언트 메세지 쓰여있음

        // printf("%s \n", s2c.ball_x);
        // printf("%s \n", s2c.ball_y);
        // printf("%s \n", s2c.mari_x);
        // printf("%s \n", s2c.mari_y);
        // printf("%s \n", s2c.maru_x);
        // printf("%s \n", s2c.maru_y);
        // printf("%s \n", s2c.score);

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

        // pthread_t snd_thread, rcv_thread;
        // void *thread_return;

        // pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
        // pthread_join(snd_thread, &thread_return);

        // pthread_join(rcv_thread, &thread_return);
        // close(sock);
    }
    close(new_socket);
    return 0;
}