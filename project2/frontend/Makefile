
all: library
	

library: libfbdev.o lodepng.o menu.o move_left.o drawLCD.o
	arm-linux-gnueabi-ar rc libmylib.a libfbdev.o lodepng.o menu.o move_left.o drawLCD.o

libfbdev.o: libfbdev/libfbdev.c libfbdev/libfbdev.h
	arm-linux-gnueabi-gcc -o libfbdev.o -c libfbdev/libfbdev.c 
	
lodepng.o: lodepng/lodepng.c lodepng/lodepng.h
	arm-linux-gnueabi-gcc -o lodepng.o -c lodepng/lodepng.c

menu.o: display/menu.c display/menu.h
	arm-linux-gnueabi-gcc -o menu.o -c display/menu.c

move_left.o: display/move_left.c display/move_left.h
	arm-linux-gnueabi-gcc -o move_left.o -c display/move_left.c

drawLCD.o: display/drawLCD.c display/drawLCD.h
	arm-linux-gnueabi-gcc -o drawLCD.o -c display/drawLCD.c

