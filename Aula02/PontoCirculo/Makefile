all: main.o circulo.o ponto.o
	gcc main.o circulo.o ponto.o -o main -std=c99 -Wall

ponto.o:
	gcc -c ponto.c

circulo.o:
	gcc -c circulo.c

main.o:
	gcc -c main.c

clean:
	rm *.o main

run:
	./main