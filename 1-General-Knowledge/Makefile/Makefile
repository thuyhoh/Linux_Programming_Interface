CC := gcc
FLAG := -I.

INC_FILE := hello.h


%%.o: %.c $(INC_FILE)
	$(CC) -I . -c -o $@ $<


hello:
	gcc -o hello main.c hello.c -I .
hellomake: hello.o  main.o
	$(CC) -o $@ $^ $(FLAG)

