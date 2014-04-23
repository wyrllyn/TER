program: main.o parser.o methods.o
	gcc main.o parser.o methods.o -o program -std=c99 

main.o: main.c parser.c
	gcc -c main.c -o main.o -std=c99 

methods.o: methods.c
	gcc -c methods.c -o methods.o -std=c99 

parser.o: parser.c
	gcc -c parser.c -o parser.o -std=c99 

clean:
	rm -rf *.o