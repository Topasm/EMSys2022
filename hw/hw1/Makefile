all: 1.o 2.o 3.o 4.o myProject.h
	$(CC) -o final.elf  1.o 2.o 3.o 4.o

1.o: 1.c myProject.h
	$(CC) -c -o 1.o 1.c

clean:
	rm *.o final.elf