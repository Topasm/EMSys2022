LIBRARY_DIR := libfbdev build
APPS_DIR :=   jpgViewer jpgAnimation

all: library apps
	
apps: library $(APPS_DIR)

$(APPS_DIR):
	$(MAKE) -C $@

library: $(LIBRARY_DIR) libpng.a
	arm-linux-gnueabi-ar rc libmylib.a lib/libpng.a

$(LIBRARY_DIR):
	$(MAKE) -C $@
	arm-linux-gnueabi-ar rc libmylib.a $@/$@.o

.PHONY: all $(LIBRARY_DIR) $(APPS_DIR) library apps
