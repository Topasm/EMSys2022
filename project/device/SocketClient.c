#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080


int main(int argc, char const* argv[])
{
    int sock = 0, value_Read, client_file_descriptor;
    struct sockaddr_in server_address;
    char* message = "Message from client please respond";
    char buffer[1024] =  {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
         printf("\n Error while creation of Socket \n");
         return -1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons (PORT) ;

    //IPv4와 IPv6 주소를 문자에서 이진수로 변환 
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
         printf("\nInvalid server address/ Address not found \n");
         return -1;
     }

     //connect 명령어로 소켓 서버로 연결함
    if ((client_file_descriptor= connect(sock, (struct sockaddr*)&server_address, sizeof (server_address)))< 0) {
        printf("\nConnection Failed with the server \n");
        return -1;
    }

    //send 명령어로 메세지를 소켓 서버로 보냄 
    send (sock, message, strlen (message), 0);
    printf("Message from Client Successfully Sent\n");
    value_Read = read(sock, buffer, 1024);
    printf("Response from Server: %s\n", buffer);

    //연결된 소켓 닫음
    close(client_file_descriptor);
    return 0;
}