CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar
LIBRARY_DIR := frontend device backend


all: mju_baegu.out


mju_baegu.out: $(LIBRARY_DIR)
	$(CC) -o mju_baegu.out main.c -lpthread -l mylib -L./frontend  -l MyPeri -L./device/libs -l PE -L./backend -l m


$(LIBRARY_DIR):
	$(MAKE) -C $@

.PHONY: all $(LIBRARY_DIR)
