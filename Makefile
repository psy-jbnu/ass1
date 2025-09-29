CC = gcc
CFLAGS = -Wall -g
TARGET = main
OBJS = main.o print.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c print.h device.h
	$(CC) $(CFLAGS) -c main.c

print.o: print.c print.h device.h
	$(CC) $(CFLAGS) -c print.c

clean:
	rm -f $(TARGET) $(OBJS)
	rm -f *.dat

test:
	./main init data.txt data_binary.dat
	./main print data_binary.dat
	./main update data_binary.dat 1003 - off
	./main update data_binary.dat 1003 - activate
