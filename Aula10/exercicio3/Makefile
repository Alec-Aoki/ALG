all: main.o ABB.o item.o
	gcc main.o ABB.o item.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c

ABB.o:
	gcc -c ABB.c

main.o:
	gcc -c main.c

clean:
	rm *.o main
	clear

run:
	./main

zip:
	zip -R entrega.zip . '*.c' '*.h' 'Makefile'