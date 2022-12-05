#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

 int main(int arg, char const* argv[])
{
int sock = 0, value_Read, client_file_descriptor;
struct sockaddr_in server_address;
char* message ="Hello, Message from Client, Please Response";
char buffer [1024] = { 0 };
if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
printf("In Error while creation of Socket \n");
return -1;
}

server_address.sin_family = AF_INET;
server_address.sin_port = htons(PORT);

// Converting the IPv4 and IPv6 addresses from text to binary format 
if (inet_pton(AF_INET, "192.168.108.15", &server_address.sin_addr) <= 0) {
 printf("\nInvalid server address/ Address not found \n");
return -1;
}
//Going to connet to the socket server using connect method 
if ((client_file_descriptor = connect(sock, (struct sockaddr*)&server_address, sizeof (server_address))) < 0) {
printf("\nConnection Failed with the server \n");
return -1;
}
//send message to socket server using send method 
send (sock, message, strlen(message), 0);
printf("Message from Client Successfully Sent\n");
while(1){
value_Read = read(sock, buffer, 1024);
printf("Response from Server: %s\n", buffer);
}
// closing the connected socket
close(client_file_descriptor);
return 0;
}