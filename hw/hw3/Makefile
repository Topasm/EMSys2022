all: libMyPeri.a

libMyPeri.a: button.o led.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
textlcd.o: textlcd.h textlcd.c
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
temperature.o: temperature.h temperature.c
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o
accelMagGyro.o: accelMagGyro.h accelMagGyro.c
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o
clean: 
	rm -f *.o *.a
