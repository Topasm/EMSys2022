CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar
LIBRARY_DIR := libfbdev


all: mju_baegu.out


mju_baegu.out: library
	$(CC) -o mju_baegu.out main.c -lpthread -l mylib

library: $(LIBRARY_DIR)
	arm-linux-gnueabi-gcc -o libfbdev/libfbdev.o -c libfbdev/libfbdev.c -l m -mfloat-abi=hard
	arm-linux-gnueabi-ar rc libmylib.a libfbdev/libfbdev.o

.PHONY: all $(LIBRARY_DIR) library
