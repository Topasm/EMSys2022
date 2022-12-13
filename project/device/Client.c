#include "Client.h"

int client_init(char *servip)
{
    int sock = 0;
    struct sockaddr_in server_address;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("In Error while creation of Socket \n");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, servip, &server_address.sin_addr) <= 0)
    {
        printf("\nInvalid server address/ Address not found \n");
        return -1;
    }

    // 서버에 연결
    if ((client_file_descriptor = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        printf("\nConnection Failed with the server \n");
        return -1;
    }
    // Going to connet to the socket server using connect method
    return sock;
}
