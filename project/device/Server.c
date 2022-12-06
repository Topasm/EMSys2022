#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int arg, char const *argv[])
{
    int mari_x, maru_x, ball_x;
    int server_file_desc, new_socket, value_Read;
    struct sockaddr_in socket_Address;
    int option = 1;
    int address_Length = sizeof(socket_Address);
    char strCmd[100];
    char buffer[100] = {0};
    int result;
    sprintf(strCmd, "./게임 '%d, %d, %d'", mari_x, maru_x, ball_x);
    result = system(strCmd); //문자열 그대로 실행시키는 함수

    // Creating socket file descriptor
    if ((server_file_desc = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Failed to Obtained Socket File Descriptor");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_file_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)))
    {
        perror("Setting Socket Failed.");
        exit(EXIT_FAILURE);
    }
    socket_Address.sin_family = AF_INET;
    socket_Address.sin_addr.s_addr = INADDR_ANY;
    socket_Address.sin_port = htons(PORT);
    // Forcefully attaching socket to the port 8080
    if (bind(server_file_desc, (struct sockaddr *)&socket_Address,
             sizeof(socket_Address)) < 0)
    {
        perror("Bind File Descriptor on Port 8080 Failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is Waiting for Client Connection! \n");
    if (listen(server_file_desc, 3) < 0)
    {
        perror("Listening Failed.");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_file_desc, (struct sockaddr *)&socket_Address, (socklen_t *)&address_Length)) < 0)
    {
        perror("Connect is not Accepted.");
        exit(EXIT_FAILURE);
    }

    // Reading the Message sent from Server
    value_Read = read(new_socket, buffer, 100);
    // printf ("Message from Client: %s \n", buffer); //버퍼에 클라이언트 메세지 쓰여있음

    while (1)
    {
        printf("Message from Client: %s \n", buffer); //버퍼에 클라이언트 메세지 쓰여있음

        send(new_socket, strCmd, strlen(strCmd), 0);
        printf("Message from Server is Sent to client\n");
    } // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_file_desc, SHUT_RDWR);
    return 0;
}