# TODO: Fix everything to include the proper headers.

all: main

command.o: command.c command.h

input.o: input.c input.h

input_handler.o: input_handler.c input_handler.h

main.o: main.c
