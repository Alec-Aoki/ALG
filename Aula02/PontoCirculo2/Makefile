all: main.o circulo.o ponto.o
	gcc main.o circulo.o ponto.o -o main -std=c99 -Wall -lm

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

zip:
	zip -R entrega.zip . '*.c' '*.h' 'Makefile'
