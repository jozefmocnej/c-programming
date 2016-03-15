CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
SOURCES = main.c k.c hof.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = game

all: $(SOURCES) $(EXECUTABLE)

game: $(OBJECTS)
	#cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o $(EXECUTABLE)
	
main.o: main.c k.h hof.h
	$(CC) $(CFLAGS) -c $< $(LDLIBS)
	
k.o: k.c k.h
	$(CC) $(CFLAGS) -c $< $(LDLIBS)
	
hof.o: hof.c hof.h
	$(CC) $(CFLAGS) -c $< $(LDLIBS)
	
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
