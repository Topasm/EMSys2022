//최종 프로젝트 파일

#include "main.h"
static pthread_t rcv_thread;
int sock = 0;
char buffers[100];
static pthread_t ServerTh_id;

typedef struct
{
    int ball_x;
    int ball_y;
    int mari_x;
    int mari_y;
    int maru_x;
    int maru_y;
    int score; //기본 4 0 이면 1번 승 8면 2번승
} server2client;

typedef struct
{
    int whichChar; //어떤 캐릭터 선택
    int gyrodata;
}client2server;

<<<<<<< HEAD

=======
char buffers[100];

static pthread_t ServerTh_id;
>>>>>>> 0e3e9c52645ea18aca54da29c15f0d4ffd35444e

static pthread_t BgmTh_id;

void PE_init()
{
    ball = generate_ball(60.0, 0.0);
    // mari_obj = generate_character(10, 300);
    // maru_obj = generate_character(20, 10);
}

static void *ClientThFunc(void)
{
    sock = client_init();

    send(sock, strCmd, strlen(strCmd), 0);
    // send message to socket server using send method
    printf("Message from Client Successfully Sent\n");
    while (1)
    {
        value_Read = read(sock, strCmd, 100);
        printf("Response from Server: %s\n", strCmd);
    }
    send(sock, strCmd, strlen(strCmd), 0);
}

static void *Server_thread(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    server_init();

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

// BGM start
static void *Bgm_thread(void)
{   
    // while문을 돌면서 음악 재생
    buzzerInit();

    while(1)
    {
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(0);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);

    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);

    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);
    return 0;
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
    // server_init();
    pthread_create(&rcv_thread, NULL, ClientThFunc, (void *)&sock);

    // int i = 0;
    pthread_create(&ServerTh_id,NULL, Server_thread,NULL);
    
    pthread_create(&BgmTh_id,NULL, Server_thread,NULL);

    // client_init();
    // int i = 0;
    dispaly_menu();


    // Reading the Message sent from Server
    //value_Read = read(new_socket, buffers, 100);
    // printf ("Message from Client: %s \n", buffer); //버퍼에 클라이언트 메세지 쓰여있음
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
        close(new_socket);

        // closing the listening socket
        shutdown(server_file_desc, SHUT_RDWR);
    }
    close(sock);
    close(client_file_descriptor);
    return 0;
}
