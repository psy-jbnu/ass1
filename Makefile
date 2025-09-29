main: main.o print.o device.h
	gcc -o main main.o print.o device.h
main.o: main.c 
print.o: print.c print.h
