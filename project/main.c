// 최종 프로젝트 파일
#include "main.h"
int sock = 0;
int new_socket = 0;
char servip[30] = {0};
int jumsu = 4;

int currentCount = 1;
int Gcontact = 0;

static pthread_t ServerTh_id;
static pthread_t BgmTh_id;
static pthread_t rcv_thread;
static pthread_t thled;

typedef struct client2server
{
    int whichChar; // 어떤 캐릭터 선택
    int gyrodata;
} c2s;

c2s c2s2;
c2s c2s3;

void PE_init()
{
    ball = generate_ball(120, 10);
    mari_obj = generate_character(120, 200);
    maru_obj = generate_character(720, 200);
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

        send(sock, (struct client2server *)&c2s2, sizeof(c2s2), 0);
        //
        printf("%d", c2s2.gyrodata);
        usleep(10000);
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
    // while문을 돌면서 음악 재생

    printf("buzzer on");
    buzzerInit();

    while (1)
    {
        buzzerPlaySong(8);

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
    ledLibInit();
    fb_clear();
    png_init();
    txtlcd_Init();
    PE_init();
    led(jumsu);
    const char* str1 = "MARI MARU";
	const char* str2 = "VOLLEYBALL";
    lcdtextwrite(str1, str2,1);
    lcdtextwrite(str1, str2,2);
    int charselect = 0;

    dispaly_menu();
    charselect = select_player();
    if (charselect == 1)
    {

        
        const char* str1 = "player selected";
	    const char* str2 = "MARU";
        lcdtextwrite(str1, str2,1);
        lcdtextwrite(str1, str2,2);
        printf("write your ip : ");
        scanf("%s", servip);
        printf("%s\n", servip);
        pthread_create(&rcv_thread, NULL, ClientThFunc, (void *)&sock);
    }
    else if (charselect == 2)
    {
        pthread_create(&ServerTh_id, NULL, Server_thread, NULL);
        const char* str1 = "player selected";
	    const char* str2 = "MARI";
        lcdtextwrite(str1, str2,1);
        lcdtextwrite(str1, str2,2);
        printf("type ready to start : ");
        scanf("%s", servip);
    }

    pthread_create(&BgmTh_id, NULL, Bgm_thread, NULL);

    while (charselect == 1)
    {
        c2s2.whichChar = 1;
        update_whwhd();
        update_screen();
        c2s2.gyrodata = -2 * get_dx();
    }

    // 211.15

    while (charselect == 2)
    {
        if (c2s2.whichChar == 1)
        {
            mari_obj->vel.x = -2 * get_dx();
            maru_obj->vel.x = -2 * c2s2.gyrodata;

            calculateG(ball, 0.8);

            int contact1 = CheckCollisionAnB(ball, mari_obj);
            if (contact1 == 1)
            {
                CheckImpulseAnB(ball, mari_obj);
                contact1 = 0;
            }
            int contact2 = CheckCollisionAnB(ball, maru_obj);
            if (contact2 == 1)
            {
                CheckImpulseAnB(ball, maru_obj);
                contact2 = 0;
            }
            Gcontact = ContactGround(ball, 1);
            if (Gcontact > 0)
            {

                if (Gcontact > 512)
                {

                    jumsu++;
                    printf("contaced");
                    printf("the score is %d\n", (int)jumsu);
                    led(jumsu);
                }
                else if (Gcontact < 512)
                {

                    jumsu--;
                    printf("contaced");
                    printf("the score is %d\n", (int)jumsu);
                    led(jumsu);
                }
            }
            calculateP(ball);
            calculateP(mari_obj);
            calculateP(maru_obj);

            CharContactEdge(mari_obj, maru_obj);
            ballContactEdge(ball);
            update_background();
            update_ball((int)ball->pos.x, (int)ball->pos.y);
            update_mari((int)mari_obj->pos.x, (int)mari_obj->pos.y);
            update_maru((int)maru_obj->pos.x, (int)maru_obj->pos.y);
            update_screen();
            if (jumsu == 8)
            {
                update_win1();
                update_screen();
                buzzerStopSong();
                break;
            }
            if (jumsu == 0)
            {
                update_win2();
                update_screen();
                buzzerStopSong();
                break;
            }
        }
    }

    fb_close();
    // closing the listening socket
    shutdown(new_socket, SHUT_RDWR);
    close(sock);
    close(new_socket);
    ledLibExit();
    return 0;
}