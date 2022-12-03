LIBRARY_DIR := libfbdev


all: library
	

library: $(LIBRARY_DIR)
	arm-linux-gnueabi-gcc -o libfbdev/libfbdev.o -c libfbdev/libfbdev.c -l m
	arm-linux-gnueabi-ar rc libmylib.a libfbdev/libfbdev.o

.PHONY: all $(LIBRARY_DIR) library
