
all: library
	

library: libfbdev.o lodepng.o menu.o move_left.o drawLCD.o select_player_btn.o
	arm-linux-gnueabi-ar rc libmylib.a libfbdev.o lodepng.o menu.o move_left.o drawLCD.o select_player_btn.o

libfbdev.o: libfbdev/libfbdev.c libfbdev/libfbdev.h
	arm-linux-gnueabi-gcc -o libfbdev.o -c libfbdev/libfbdev.c  -lpthread
	
lodepng.o: lodepng/lodepng.c lodepng/lodepng.h
	arm-linux-gnueabi-gcc -o lodepng.o -c lodepng/lodepng.c -lpthread

menu.o: display/menu.c display/menu.h
	arm-linux-gnueabi-gcc -o menu.o -c display/menu.c -lpthread

move_left.o: display/move_left.c display/move_left.h
	arm-linux-gnueabi-gcc -o move_left.o -c display/move_left.c -lpthread

drawLCD.o: display/drawLCD.c display/drawLCD.h
	arm-linux-gnueabi-gcc -o drawLCD.o -c display/drawLCD.c -lpthread

select_player_btn.o: display/select_player_btn.c display/select_player_btn.h
	arm-linux-gnueabi-gcc -o select_player_btn.o -c display/select_player_btn.c

