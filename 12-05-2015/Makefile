all :main

main:main.o procedure.o
	gcc -o main main.o  procedure.o -lpthread

procedure.o :procedure.c
	gcc -c -g -o procedure.o procedure.c

main.o : main.c
	gcc -c -g -o main.o main.c

clean:
	rm -f main
	rm -f  *.o