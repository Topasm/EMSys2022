all: libSocket.a

libSocket.a: Server.o Client.o
	arm-linux-gnueabi-ar rc libSocket.a Server.o Client.o

Server.o : Server.c
	arm-linux-gnueabi-gcc -c Server.c -lpthread -o Server.o

Client.o : Client.c
	arm-linux-gnueabi-gcc -c Client.c -lpthread -o Client.o

clean: 
	rm -f *.o *.a
