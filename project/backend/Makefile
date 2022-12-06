CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: libPE.a


libPE.a: PEcollide.o PEobject.o PEworld.o
	$(AR) rc libPE.a PEcollide.o PEworld.o PEobject.o

PEcollide.o: PEcollide.h PEcollide.c
	$(CC) -c PEcollide.c -o PEcollide.o -lpthread -l m

PEobject.o: PEobject.h PEobject.c
	$(CC) -c PEobject.c -o PEobject.o -lpthread -l m


PEworld.o: PEworld.h PEworld.c
	$(CC) -c PEworld.c -o PEworld.o -lpthread -l m

	
test:
	gcc -o test.out PhysicsEngine.c PEcollide.c PEobject.c PEworld.c
