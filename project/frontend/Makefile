LIBRARY_DIR := libfbdev libjpeg
APPS_DIR :=   jpgViewer jpgAnimation

all: library apps
	
apps: library $(APPS_DIR)

$(APPS_DIR):
	$(MAKE) -C $@

library: $(LIBRARY_DIR) libjpeg/libjpeg.a
	arm-linux-gnueabi-ar rc libmylib.a libjpeg/libjpeg.a

$(LIBRARY_DIR):
	$(MAKE) -C $@
	arm-linux-gnueabi-ar rc libmylib.a $@/$@.o

.PHONY: all $(LIBRARY_DIR) $(APPS_DIR) library apps
