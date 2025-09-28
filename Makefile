main: main.o print.o device.o
	gcc -o main main.o print.o device.o
main.o: main.c 
print.o: print.c print.h
device.o: device.c device.h
