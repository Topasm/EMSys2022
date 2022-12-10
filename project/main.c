// 최종 프로젝트 파일
// 최종 프로젝트 파일
#include "main.h"
int sock = 0;
int new_socket = 0;
char servip[30] = {0};

static pthread_t ServerTh_id;
static pthread_t BgmTh_id;
static pthread_t rcv_thread;

typedef struct server2client
{
    int ball_x;
    int ball_y;
    int mari_x;
    int maru_x;
    int score;
} s2c;

s2c s2c2;

typedef struct client2server
{
    int whichChar; // 어떤 캐릭터 선택
    int gyrodata;
} c2s;

c2s c2s2;

void PE_init()
{
    ball = generate_ball(120, 0.0);
    mari_obj = generate_character(120, 200);
    maru_obj = generate_character(700, 200);
}
static void *ClientThFunc(void)
{

    sock = client_init(servip);

    // value_Read = recv(sock, (struct server2client *)&s2c, sizeof(s2c), 0);
    // send message to socket server using send method
    // printf("Message from Client Successfully Sent\n");
    while (1)
    {
        // value_Read = read(sock, strCmd, 100);

        value_Read = recv(sock, (struct server2client *)&s2c2, sizeof(s2c2), 0);
        if (value_Read < 0)
        {
            // printf("error");
        }
        else
        {
            printf("%d \n", s2c2.ball_x);
            printf("%d \n", s2c2.ball_y);
            printf("%d \n", s2c2.mari_x);
            printf("%d \n", s2c2.mari_y);
            printf("%d \n", s2c2.maru_x);
            printf("%d \n", s2c2.maru_y);
            printf("%d \n", s2c2.score);
        }
        send(sock, (struct client2server *)&c2s2, sizeof(c2s2), 0);
    }
}

static void *Server_thread(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    new_socket = server_init();
    if (new_socket < 0)
    {
        printf("get server fail");
    }

    while (1)
    {
        send(new_socket, (struct server2client *)&s2c2, sizeof(s2c2), 0);
        value_Read = recv(new_socket, (struct client2server *)&c2s2, sizeof(c2s2), 0);
        // printf("Message from Client: %s \n", buffers); // 버퍼에 클라이언트 메세지 쓰여있음
        if (value_Read > 0)
        {
            printf("%d \n", c2s2.whichChar);
            printf("%d \n", c2s2.gyrodata);
        }

        // printf("Message from Server is Sent to client\n");
    } // closing the connected socket
}

// BGM start
static void *Bgm_thread(void)
{
{
    // while문을 돌면서 음악 재생

    printf("buzzer on");
    buzzerInit();
    // buzzerPlaySong(2);

    while (1)
    while (1)
    {
        //         buzzerPlaySong(2);
        // usleep(200000);
        buzzerStopSong();
        // usleep(200000);

        // usleep(200000);
    }
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
    pthread_create(&BgmTh_id, NULL, Bgm_thread, NULL);
    c2s2.whichChar = select_player();
    if (c2s2.whichChar == 1)
    {

        printf("write your ip : ");
        scanf("%s", servip);
        printf("%s\n", servip);

        pthread_create(&rcv_thread, NULL, ClientThFunc, (void *)&sock);
    }
    else if (c2s2.whichChar == 2)
    {
        pthread_create(&ServerTh_id, NULL, Server_thread, NULL);
    }

    dispaly_menu();
    // 211.15

    while (1)
    {
        mari_obj->vel.x = get_dx();

        // calculateG(ball, 0.8);

        // //  int contact1 = CheckCollisionAnB(ball, mari_obj);
        // //  if (contact1 == 1)
        // //  {
        // //      CheckImpulseAnB(ball, mari_obj);
        // //      contact1 = 0;
        // //  }
        // //  int contact2 = CheckCollisionAnB(ball, mari_obj);
        // //  if (contact2 == 1)
        // //  {
        // //      CheckImpulseAnB(ball, maru_obj);
        // //      contact2 = 0;

        // //  }
        // ContactGround(ball, 1);
        // calculateP(ball);
        // calculateP(mari_obj);
        // calculateP(maru_obj);
        // update_background();
        // // printf("%d\n", (int)(ball->pos.y/1));
        // //  update_ball((int)ball->pos.x, (int)ball->pos.y);
        // //  update_mari((int)mari_obj->pos.x, (int)mari_obj->pos.y);
        // //  update_maru((int)maru_obj->pos.x, (int)maru_obj->pos.y);

        // update_screen();
        c2s2.gyrodata = mari_obj->vel.x;

        // printf("ball pose x = %f y = %f contact = %d\n", ball->pos.x, ball->pos.y, contact);
        // printf("---mari_obj pose x = %f y = %f contact = %d\n", mari_obj->pos.x, mari_obj->pos.y, contact);
    }

    fb_close();
    // closing the listening socket
    shutdown(new_socket, SHUT_RDWR);

    close(sock);
    close(new_socket);
    return 0;
}