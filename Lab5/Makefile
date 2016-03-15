all : cipher

cipher: main.o cipher.o
	gcc -std=c11 -Werror -Wall main.o cipher.o -o cipher
	
tests : test_cipher.o cipher.o
	gcc -std=c11 -Werror -Wall test_cipher.o cipher.o -o tests
	./tests
	
test_cipher.o : test_cipher.c cipher.h
	gcc -std=c11 -Werror -Wall -c test_cipher.c
	
main.o : main.c cipher.h
	gcc -std=c11 -Werror -Wall -c main.c
	
cipher.o : cipher.c cipher.h
	gcc -std=c11 -Werror -Wall -c cipher.c
	
clean :
	rm -rf main.o cipher.o test_cipher.o cipher tests
