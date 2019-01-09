
# set up the variables
CC=clang
CFLAGS =-c -Wall


all: usageExample

usageExample : usageExample.o ObjectManager.o
	$(CC) usageExample.o  ObjectManager.o -o usageExample
	
usageExample.o : usageExample.c
	$(CC) $(CFLAGS) usageExample.c
	
ObjectManager.o : ObjectManager.c
	$(CC) $(CFLAGS) ObjectManager.c
	
clean:
	rm -rf *.o usageExample