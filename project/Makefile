CC=arm-linux-gnueabi-gcc

all:
	$(CC) jpgAnimation.c -o jpgAnimation -L../ -L../libjpeg -lpthread -l mylib -l jpeg



LIBRARY_DIR := libfbdev


all: library
	

library: $(LIBRARY_DIR)
	arm-linux-gnueabi-gcc -o libfbdev/libfbdev.o -c libfbdev/libfbdev.c -l m -mfloat-abi=hard
	arm-linux-gnueabi-ar rc libmylib.a libfbdev/libfbdev.o

.PHONY: all $(LIBRARY_DIR) library
