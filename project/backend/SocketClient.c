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
}