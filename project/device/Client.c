#include "client.h"

void client_init()
{
    int sock = 0, value_Read, client_file_descriptor;
    struct sockaddr_in server_address;
    // char *message = "클라이언트에서 보내는 x, y좌표"; //서버로 보내는 메세지

    int result;
    sprintf(strCmd, "./gyroTest '%d, %d, %d'", gyro[0], gyro[1], gyro[2]);
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
}