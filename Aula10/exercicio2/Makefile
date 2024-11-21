all: main.o ab.o item.o
	gcc main.o ab.o item.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c

ab.o:
	gcc -c ab.c

main.o:
	gcc -c main.c

clean:
	rm *.o main
	clear

run:
	./main

zip:
	zip -R entrega.zip . '*.c' '*.h' 'Makefile'