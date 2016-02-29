CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
SOURCES = main.c k.c hof.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = game

all: $(SOURCES) $(EXECUTABLE)

game: $(OBJECTS)
	#cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) -o $(EXECUTABLE)
	
main.o: main.c
	$(CC) $(CFLAGS) $(LDLIBS) -c $<
	
k.o: k.c k.h
	$(CC) $(CFLAGS) $(LDLIBS) -c $<
	
hof.o: hof.c hof.h
	$(CC) $(CFLAGS) $(LDLIBS) -c $<
	
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
