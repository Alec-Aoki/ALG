all: main.o Pilha.o item.o
	gcc main.o Pilha.o item.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c

Pilha.o:
	gcc -c Pilha.c

balanceada.o:
	gcc -c main.c

clean:
	rm *.o main
	clear

run:
	./main

zip:
	zip -R entrega.zip . '*.c' '*.h' 'Makefile'
