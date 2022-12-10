// 최종 프로젝트 파일
#include "main.h"
int sock;
int new_socket;
char servip[30] = {0};

static pthread_t ServerTh_id;
static pthread_t BgmTh_id;
static pthread_t rcv_thread;

// void get_ip()
// {
//     scanf
// }

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
    ball = generate_ball(60.0, 0.0);
    // mari_obj = generate_character(10, 300);
    // maru_obj = generate_character(20, 10);
}
// static void *ClientThFunc(void)
// {
//     sock = client_init();

//     // value_Read = recv(sock, (struct server2client *)&s2c, sizeof(s2c), 0);
//     // send message to socket server using send method
//     printf("Message from Client Successfully Sent\n");
//     while (1)
//     {

//         value_Read = recv(sock, (struct server2client *)&s2c2, sizeof(s2c2), 0);
//         printf("%d00 \n", s2c2.ball_x);
//         printf("%daa \n", s2c2.ball_y);
//         printf("%dbb \n", s2c2.mari_x);

//         printf("%ddd \n", s2c2.maru_x);

//         printf("%dgg \n", s2c2.score);
//         send(sock, (struct client2server *)&c2s2, sizeof(c2s2), 0);
//     }
// }

static void *Server_thread(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    new_socket = server_init();

    while (1)
    {
        send(new_socket, (struct server2client *)&s2c2, sizeof(s2c2), 0);
        value_Read = recv(new_socket, (struct client2server *)&c2s2, sizeof(c2s2), 0);
        printf("%dff \n", c2s2.whichChar);
        printf("%dhh \n", c2s2.gyrodata);
    }
}

// BGM start
static void *Bgm_thread(void)
{
    // while문을 돌면서 음악 재생

    printf("buzzer on");
    buzzerInit();

    while (1)
    {
        // buzzerPlaySong(2);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(1);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(0);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(1);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(400000);

        // buzzerPlaySong(2);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(2);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(2);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(400000);

        // buzzerPlaySong(1);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(1);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(200000);
        // buzzerPlaySong(1);
        // usleep(200000);
        // buzzerStopSong();
        // usleep(400000);
    }
}

int main(int argc, char **argv)
{

    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;

    printf("write your ip : ");
    scanf("%s", servip);
    argv[1] = servip;
    // servip client로 메세지 send
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

    pthread_create(&ServerTh_id, NULL, Server_thread, NULL);
    send(new_socket, servip, strlen(servip), 0);

    // pthread_create(&rcv_thread, NULL, ClientThFunc, (void *)&sock);

    dispaly_menu();

    while (1)
    {

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
        // closing the listening socket
        shutdown(new_socket, SHUT_RDWR);
    }
    // close(sock);
    close(new_socket);
    return 0;
}