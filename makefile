CC = gcc
CFLAGS = -std=c11

OBJECTS = lab4.o

all:	lab4

lab4:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)  -o $@

lab4.o:	lab4.c

clean:
	rm -f *.o lab4

