#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8080

int  value_Read, client_file_descriptor;
char strCmd[100];

int client_init();