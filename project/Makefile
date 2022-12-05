CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar
LIBRARY_DIR := frontend


all: mju_baegu.out


mju_baegu.out: $(LIBRARY_DIR) library
	$(CC) -o mju_baegu.out main.c -lpthread -l mylib -L./frontend  -l m -mfloat-abi=hard


$(LIBRARY_DIR):
	$(MAKE) -C $@

.PHONY: all $(LIBRARY_DIR) library
