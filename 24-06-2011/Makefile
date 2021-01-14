all:main

main:main.o procedure.o monitor.o
	gcc -o main  procedure.o  monitor.o main.o

main.o:main.c
	gcc -c -g -o main.o main.c

procedure.o:procedure.c
	gcc -c -g -o procedure.o procedure.c

monitor.o:monitor.c
	gcc -c -g -o monitor.o monitor.c

clean:
	rm -f *.o
	rm -f main