all: 1.o 2.o 3.o main.o myProject.h
	$(CC) -o final.elf main.o 1.o 2.o 3.o

main.o: main.c myProject.h
	gcc -c -o main.o main.c 

clean:
	rm *.o final.elf