CFLAGS:=-Wall -Werror
DEBUG:=false

ifeq ($(DEBUG),true)
	CFLAGS:=$(CFLAGS) -g
endif

all: main

main: command.o input.o input_handler.o main.o prompt.o
	gcc -o $@ $^

command.o: command.c command.h
	gcc $(CFLAGS) -c $<

input.o: input.c input.h
	gcc $(CFLAGS) -c $<

input_handler.o: input_handler.c input_handler.h command.h
	gcc $(CFLAGS) -c $<

main.o: main.c input.h input_handler.h prompt.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f *~ .*.swp *.exe *.o main

run: all
	./main
