program: main.o parser.o
	gcc main.o parser.o -o program

main.o: main.c parser.c
	gcc -c main.c -o main.o

parser.o: parser.c
	gcc -c parser.c -o parser.o

clean:
	rm -rf *.o