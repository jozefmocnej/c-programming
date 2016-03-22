CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
EXEC=forecast

all: $(EXEC)

$(EXEC): forecast.o main.c
	$(CC) $(CFLAGS) forecast.o main.c -o $(EXEC)

forecast.o: forecast.c
	$(CC) $(CFLAGS) -c forecast.c

clean:
	rm -rf *.o $(EXEC)
