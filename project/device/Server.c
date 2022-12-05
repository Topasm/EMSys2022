 #include <netinet/in.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #define PORT 8080
 int main(int arg, char const* argv[])
 {
int server_file_desc, new_socket, value_Read;
struct sockaddr_in socket_Address;
int option = 1;
int address_Length = sizeof(socket_Address);
char buffer [1024] = { 0 };
char* message = "Greetings Message from Server!!!";

// Creating socket file descriptor
if ((server_file_desc = socket (AF_INET, SOCK_STREAM, 0)) == 0) 
{
perror ("Failed to Obtained Socket File Descriptor");
exit (EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080 
if (setsockopt (server_file_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof (option))) {
perror ("Setting Socket Failed.");
exit(EXIT_FAILURE);
}

socket_Address.sin_family = AF_INET;
socket_Address.sin_addr.s_addr = INADDR_ANY;
socket_Address.sin_port = htons (PORT);
// Forcefully attaching socket to the port 8080 
if (bind(server_file_desc, (struct sockaddr*)&socket_Address,
sizeof (socket_Address)) < 0) {
perror ("Bind File Descriptor on Port 8080 Failed");
exit (EXIT_FAILURE);
}
printf ("Server is Waiting for Client Connection! \n");
if (listen (server_file_desc, 3) < 0) {
perror ("Listening Failed.");
exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_file_desc, (struct sockaddr*)&socket_Address, (socklen_t*)&address_Length)) < 0) {
perror ("Connect is not Accepted.");
exit(EXIT_FAILURE);
}
//Reading the Message sent from Server
value_Read = read(new_socket, buffer, 1024);
printf ("Message from Client: %s \n", buffer); 
send (new_socket, message, strlen(message), 0); 
printf ("Message from Server is Sent to client\n");
// closing the connected socket
close(new_socket);
// closing the listening socket
shutdown (server_file_desc, SHUT_RDWR);
return 0;
}
