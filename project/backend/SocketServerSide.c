#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char const* argv[])
{
    int server_file_desc, new_socket, value_Read;
    struct sockaddr_in socket_Address;
    int option = 1;
    int addres_Length = sizeof(socket_Address);
    char buffer[1024] = {0};
    char* message = "Greetings Message from Server";

    //소켓 통신 FD 만들기
    if((server_file_desc = socket(AF_INET, SOCK_STREAM, 0))==0)
    {
        perror("Failed to Obtain Socket FD");
        exit(EXIT_FAILURE);
    }

    //포트 8080으로 연결
    if(setsockopt(server_file_desc, SOL_SOCKET,
                    SO_REUSEADDR|SO_REUSEPORT, &option,
                    sizeof(option))){
            perror("Setting Socket Failed");
            exit(EXIT_FAILURE);
    }

    socket_Address.sin_family = AF_INET;
    socket_Address.sin_addr.s_addr = INADDR_ANY;
    socket_Address.sin_port = htons(PORT);

    if(bind(server_file_desc, (struct sockaddr*)&socket_Address,
    sizeof(socket_Address))<0)
    {
        perror("Bind File Descriptor on Port 8080 Failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is Waiting for Client Connection!\n");

    if(listen(server_file_desc, 3)< 0){
        perror("Listening Failed.");
        exit(EXIT_FAILURE);
    }

    if((new_socket = accept(server_file_desc,(struct sockaddr*)&socket_Address,))








    
}