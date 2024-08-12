all: main.o racional.o
	gcc main.o racional.o -o racional -std=c99 -Wall

racional.o:
	gcc -c racional.c

main.o:
	gcc -c main.c

clean:
	rm *.o racional