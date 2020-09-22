OBJECTS = main.o bitmap.o debug.o hash.o hex_dump.o list.o
CC= gcc

TARGET = testlib


$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

main.o: main.c
	$(CC) -c -o main.o main.c

debug.o: debug.c debug.h
	$(CC) -c -o debug.o debug.c

hex_dump.o: hex_dump.c hex_dump.h round.h
	$(CC) -c -o hex_dump.o hex_dump.c

list.o: list.c list.h
	$(CC) -c -o list.o list.c

bitmap.o: bitmap.c bitmap.h limits.h round.h
	$(CC) -c -o bitmap.o bitmap.c

hash.o: hash.c hash.h
	$(CC) -c -o hash.o hash.c

clean:
	rm $(OBJECTS) $(TARGET)
