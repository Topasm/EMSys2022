#define _XOPEN_SOURCE 200    // 값에 따라 sigaction 정의가 달라집니다.
#include <signal.h>      

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <pthread.h> 
#include <signal.h> 
#define LISTENING_PORT 50001 // Server 포트
// thread 
void *listening_thread(void *arg); 
void *client_thread(void *arg); 
void error_handling(char *message); 
#define CMD_NONE 0 
#define CMD_CONTROL 1 
#define MAX_CLIENT_NUM 10 // 서버에 붙을 수 있는 최대 Client 수
struct led_control // 현재 LED 정보 상태 
{ 
// bit 0 => first led, bit 2 => Second led , bit 7 => 7th led . set(1) => ON , 
//reset(0) => OFF 
 int ledStatus; 
 int newCmdFlag; // 새로운 명령이 왔다는 표시
 pthread_mutex_t* mutex; 
};
struct server_info // 서버의 개인 정보 
{ 
 struct led_control ledctl; 
 int threadStop; 
 int serverlistenSock; // listen 소켓
}; 
struct info_for_client //  연결된 Client의 정보 
{ 
 struct server_info* pInfo; 
 int ownSockIndex; 
 int clientSock[MAX_CLIENT_NUM]; 
}; 
struct server_info gInfo; 
struct info_for_client clientInfo; 
void alarmLedControl(unsigned char data) 
{ 
 char strCmd[80]; 
 int result; 
 sprintf(strCmd,"./ledtest  0x%02x",data); 
 result = system(strCmd); 
} 
void handle_kill_signal() { 
 gInfo.threadStop = 1; 
 if ( gInfo.serverlistenSock != -1) 
 close(gInfo.serverlistenSock); 
 signal(SIGINT, SIG_DFL); // SIG_DFL => do the default action of this signal 
 alarmLedControl(0x00); // all off 
} 
void init(struct server_info* data) 
{ 
 alarmLedControl(0x00); // LED off 
 data->ledctl.ledStatus = 0x00; 
 data->ledctl.newCmdFlag = CMD_NONE; 
 data->threadStop = 0; 
 data->serverlistenSock = -1; 
 data->ledctl.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)); 
 pthread_mutex_init( data->ledctl.mutex , NULL ); // 뮤텍스 init 
} 
int main(int argc, char *argv[]) 
{ 
 struct server_info* pInfo=&gInfo; 
 pthread_t pthreadListening; // accept client 
 struct sigaction action; 
 int *pThreadReturn; 
init(pInfo); 
 // create listening thread 
 if(pthread_create(&pthreadListening, NULL, listening_thread, pInfo) == -1) 
 { 
 error_handling("pthread_create() error\n"); 
 return -1; 
 } 
 // Add signal handler to terminate server 
 action.sa_handler = handle_kill_signal; 
 sigemptyset(&action.sa_mask); 
 action.sa_flags = 0; 
 sigaction(SIGINT, &action, NULL); // ctrl+c 
 // main thread loop 
 while(!pInfo->threadStop) 
 { 
 if ( pInfo->ledctl.newCmdFlag == CMD_CONTROL )// 새로운 명령어가 들어오면 
 { // 명령 수행 
 pInfo->ledctl.newCmdFlag = CMD_NONE; 
 alarmLedControl(pInfo->ledctl.ledStatus); 
 } 
 usleep(100000); // 100mS에 한번씩 체크 
 } 
 printf("LED control server closed.\n"); 
return 0; 
} 
//control Client acception manage 
void *listening_thread(void *arg) 
{ 
 pthread_detach(pthread_self()); // 이 스레드를 독립적으로 자원해제(스레드 종료시) 
 struct server_info* pInfo = (struct server_info*)arg; // 스레드 생성시 넘긴 데이터 
 int serv_sock, clnt_sock; 
 struct sockaddr_in serv_adr, clnt_adr; 
 socklen_t clnt_adr_sz; 
 
 pthread_t pthreadClient; // threadd receive data 
 struct info_for_client* pclientInfo = &clientInfo; 
 int i; 
pclientInfo->pInfo = pInfo; 
 for(i = 0; i < MAX_CLIENT_NUM ; i++) 
 { 
 pclientInfo->clientSock[i] = -1; 
 } 

pclientInfo->ownSockIndex = 0; 
// get server socket 
 serv_sock = socket(PF_INET, SOCK_STREAM, 0);// tcp => 0 
 if (serv_sock == -1) 
 error_handling("socket() error"); 
//soket option - reuse binded address 
 int option = 1; 
 setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); 
 memset(&serv_adr, 0, sizeof(serv_adr)); 
 serv_adr.sin_family = AF_INET; 
 serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // get ip address 
 serv_adr.sin_port = htons(LISTENING_PORT); // get port num
 // bind . for the connection request of control board 
 if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) 
 error_handling("bind() error"); 
// listen 
 if (listen(serv_sock, 10) == -1) 
 error_handling("listen() error"); 
 
 clnt_adr_sz = sizeof(clnt_adr); 
while(!pInfo->threadStop) 
{ 
 printf("ready to accept client...\n"); 
 // Client connection 요청시 수락 
 clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); 

printf("clnt_sock : %d\n", clnt_sock); 
 if(clnt_sock < 0 ) 
 { 
 error_handling("accept() error"); 
 continue; 
 } 
 // 최대 client 수를 넘었는 지 확인 
 if (pclientInfo->ownSockIndex >= MAX_CLIENT_NUM ) 
 { 
 close(clnt_sock); 
 continue; 
 } 
 // Clients 정보 구조체 수락한 client socket 정보 저장 
 printf("accept() success \n"); 
 pclientInfo->clientSock[pclientInfo->ownSockIndex] = clnt_sock; 
 pclientInfo->ownSockIndex++; 
 
 // accept and create object and create thread 
 if(pthread_create(&pthreadClient, NULL , client_thread , (void*)pclientInfo) == -1) 
 { 
 error_handling("acceptClient_thread -- pthread_create() error"); 
 close(clnt_sock); 
 } 
 
 printf("Connected Client IP : %s\n", inet_ntoa(clnt_adr.sin_addr)); 
 printf("Client Port Num : %d\n\n", ntohs(clnt_adr.sin_port)); 
 } 
close(serv_sock); 
 
 for(i = 0; i < MAX_CLIENT_NUM ; i++) 
 { 
 if (pclientInfo->clientSock[i] != -1) // 종료 될 때 현재 연결된 Client socket close
{ 
 close(pclientInfo->clientSock[i]); 
 pclientInfo->clientSock[i] = -1; 
 } 
 } 
 return 0; 
} 
#define RX_DATA_MAX 2048 
/************************************************************ 
 msg => 3 byte 
 msg[0] => 0xFE header 
 msg[1] => command 
 msg[2] => data 
************************************************************/ 
#define PKT_INDEX_HEADER 0 
#define PKT_INDEX_CMD 1 
#define PKT_INDEX_DATA 2 
#define PKT_LEN 3 
#define PKT_HEADER_VALUE 0xFE 
#define PKT_CMD_SET_LED 0x10 
#define PKT_CMD_GET_LED 0x11 
#define PKT_CMD_GET_LED_RES 0x91
void *client_thread(void *arg) 
{ 
 int clnt_sock; 
 struct info_for_client* pclientInfo = arg; 
 int clnt_sock_index = pclientInfo->ownSockIndex-1; 
 clnt_sock = pclientInfo->clientSock[clnt_sock_index]; 
 
 char rcv_buf[RX_DATA_MAX]; 
 int readBufSize,writeBufSize; 
 
 pthread_detach(pthread_self()); 
 while(!pclientInfo->pInfo->threadStop) 
 { 
 readBufSize = read(clnt_sock, rcv_buf, RX_DATA_MAX); 
 
 if(readBufSize > 0) 
 { // 메시지 프로토콜 형식 확인 
 if ( (readBufSize != PKT_LEN) || (rcv_buf[PKT_INDEX_HEADER] != 
PKT_HEADER_VALUE)) 
 { 
 continue; 
 } 
 // success 
 if (rcv_buf[PKT_INDEX_CMD] == PKT_CMD_SET_LED ) // LED set 명령 
 { 
 pclientInfo->pInfo->ledctl.ledStatus = rcv_buf[PKT_INDEX_DATA]; 
 pclientInfo->pInfo->ledctl.newCmdFlag = CMD_CONTROL; 
 } 
 else if (rcv_buf[PKT_INDEX_CMD] == PKT_CMD_GET_LED) // LED get 명령 
 { 
 // echo TX 
 rcv_buf[PKT_INDEX_CMD] = PKT_CMD_GET_LED_RES; 
 rcv_buf[PKT_INDEX_DATA] = pclientInfo->pInfo->ledctl.ledStatus ; 
 writeBufSize = write(clnt_sock, rcv_buf , PKT_LEN); 
 printf("Send data len: %d\n",writeBufSize); 
if(writeBufSize < 0) 
 { 
 printf("echo write() error\n"); 
 break; 
 } 
 } 
 } 
 else if (readBufSize == 0) 
 { 
 printf("readBufSize : 0\n"); 
 break; 
 } 
 else // readBufSize < 0 
 { 
 printf("client(%d) write error.\n", clnt_sock); 
 break; 
 } 
 } 
 printf("close clnt_sock.:%d\n",clnt_sock); 
 close(clnt_sock); 
 pclientInfo->clientSock[clnt_sock_index] = -1; 
 
 return 0; 
} 
void error_handling(char *message) 
{ 
 fputs(message, stderr); 
 fputc('\n', stderr); 
} 




