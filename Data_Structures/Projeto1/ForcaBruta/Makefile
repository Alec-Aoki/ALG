all: main.o fila.o PCV.o
	gcc main.o fila.o PCV.o -o main -std=c99 -Wall

fila.o:
	gcc -c fila.c

PCV.o:
	gcc -c PCV.c

main.o:
	gcc -c main.c

clean:
	rm *.o main

run:
	./main
