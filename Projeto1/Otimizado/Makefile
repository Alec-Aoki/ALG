all: teste2.o stack.o
	gcc teste2.o stack.o -o main -Wall -std=c99

teste.o:
	gcc -c teste2.c -o teste2.o -Wall -std=c99

stack.o:
	gcc -c stack.c -o stack.o -Wall -std=c99

run: main
	./main

clean:
	rm -f *.o main
