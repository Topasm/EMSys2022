#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8080

int main(int arg, char const *argv[])
{
     int mari_x, maru_x, ball_x;
    int sock = 0, value_Read, client_file_descriptor;
    struct sockaddr_in server_address;
    char *message = "클라이언트에서 보내는 x, y좌표"; //서버로 보내는 메세지
    char strCmd[100];
    char buffer[100] = {0};
    int result;
    sprintf(strCmd, "./게임 '%d, %d, %d'", mari_x, maru_x, ball_x);
    result = system(strCmd); //문자열 그대로 실행시키는 함수
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("In Error while creation of Socket \n");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Converting the IPv4 and IPv6 addresses from text to binary format
    if (inet_pton(AF_INET, "192.168.108.15", &server_address.sin_addr) <= 0)
    {
        printf("\nInvalid server address/ Address not found \n");
        return -1;
    }
    // Going to connet to the socket server using connect method
    if ((client_file_descriptor = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        printf("\nConnection Failed with the server \n");
        return -1;
    }
    // send message to socket server using send method
    send(sock, strCmd, strlen(strCmd), 0);
    printf("Message from Client Successfully Sent\n");
    while (1)
    {
        value_Read = read(sock, strCmd, 100);
        printf("Response from Server: %s\n", strCmd);
    }
    // closing the connected socket
    close(client_file_descriptor);
    return 0;
}