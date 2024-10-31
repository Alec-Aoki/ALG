all: compile
	gcc heapmax.o main.o -o main -std=c99 -Wall
	rm *.o

compile:
	gcc -c ../bibliotecas/impl/heapmax.c -o heapmax.o
	gcc -c main.c -o main.o

run:
	./main

clean:
	rm -f main