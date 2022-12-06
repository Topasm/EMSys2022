#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8080

int server_file_desc, new_socket, value_Read;
char strCmd[100];
char buffer[100] = {0};
void client_init();