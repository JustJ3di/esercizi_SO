all: main

main:main.o procedure.o monitor.o
	gcc -o main main.o procedure.o monitor.o

procedure.o:procedure.c 
	gcc -c -g -o procedure.o procedure.c

monitor.o:monitor_sc.c
	gcc -c -g -o monitor.o monitor_sc.c

clean :
	rm -f *.o
	rm -f main