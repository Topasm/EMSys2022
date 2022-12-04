#그래픽 파트

# todo원 그리기


arm-linux-gnueabi-gcc -o pngtest frontend.c lodepng/lodepng.c -l mylib -L. -l m


 ./configure --host=arm-linux-gnueabi CC=arm-linux-gnueabi-gcc AR=arm-linux-gnueabi-ar



 CC=arm-linux-gnueabi-gcc ./configure 

 make

 sudo make install


 arm-linux-gnueabi-gcc -o jpgtest jpgAmination_ex.c -l mylib -l jpeg -L. -L./libjpeg

 arm-linux-gnueabi-gcc -o pngtest frontend.c lodepng/lodepng.c -l mylib -L.