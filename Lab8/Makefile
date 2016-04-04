CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lm -lcurses
EXEC=bomber

all : $(EXEC)

$(EXEC) : main.c
	$(CC) $(CFLAGS) main.c $(LDLIBS) -o $(EXEC)
	
clean :
	$(RM) $(EXEC)
