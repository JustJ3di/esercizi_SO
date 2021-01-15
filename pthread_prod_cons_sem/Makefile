all:main

main:main.o procedure.o
	gcc -o main main.o procedure.o -lpthread

main.o:main.c
	gcc -c -g -o main.o main.c

procedure.o:procedure.c
	gcc -c -g -o procedure.o procedure.c

clean:
	rm -f *.o
	rm -f main
