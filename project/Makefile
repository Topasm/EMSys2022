CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar
LIBRARY_DIR := frontend device backend


all: mju_baegu2.out


mju_baegu2.out: $(LIBRARY_DIR)
	$(CC) -o mju_baegu2.out main.c -l mylib -L./frontend  -l MyPeri -L./device/libs -l PE -L./backend -l Socket -L./device -l m -lpthread


$(LIBRARY_DIR):
	$(MAKE) -C $@

.PHONY: all $(LIBRARY_DIR)
