# TODO: Fix everything to include the proper headers.

all: main.c
	gcc main.o main.c command.o input.o input_handler.o

command.o: command.c command.h
	gcc -c command.c 

input.o: input.c input.h
	gcc -c input.c 

input_handler.o: input_handler.c input_handler.h
	gcc -c input_handler.c

main.o: main.c
	gcc -c main.c

run: all
	./a.out
