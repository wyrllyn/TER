program: main.o parser.o methods.o
	gcc main.o parser.o methods.o -o program -std=c99 -O3

main.o: main.c parser.c
	gcc -c main.c -o main.o -O3 -std=c99

methods.o: methods.c
	gcc -c methods.c -o methods.o -O3 -std=c99

parser.o: parser.c
	gcc -c parser.c -o parser.o -O3 -std=c99

clean:
	rm -rf *.o