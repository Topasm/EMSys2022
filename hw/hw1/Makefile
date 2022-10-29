all: 1.o 2.o 3.o main.o myProject.h
	gcc -o final.elf main.o 1.o 2.o 3.o

main.o: main.c myProject.h
	gcc -c -o main.o main.c

1.o: 1.c myProject.h
	gcc -c -o 1.o 1.c

2.o: 2.c myProject.h
	gcc -c -o 2.o 2.c

3.o: 3.c myProject.h
	gcc -c -o 3.o 3.c

clean:
	rm *.o final.elf