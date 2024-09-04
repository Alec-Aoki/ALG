all: main.o Deque.o item.o
	gcc main.o Deque.o item.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c

Deque.o:
	gcc -c Deque.c

main.o:
	gcc -c main.c

clean:
	rm *.o main
	clear

run:
	./main

zip:
	zip -R entrega.zip . '*.c' '*.h' 'Makefile'
