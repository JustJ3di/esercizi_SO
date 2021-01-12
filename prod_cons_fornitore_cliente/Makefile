all: main

main:main.o procedure.o monitor_signal_continue.o
	gcc -o main main.o procedure.o monitor_signal_continue.o

main.o:main.c
	gcc -c -g -o main.o main.c

procedure.o :procedure.c
	gcc -c -g -o procedure.o procedure.c

monitor_signal_continue.o:monitor_signal_continue.c
	gcc -c -g -o monitor_signal_continue.o monitor_signal_continue.c

clean:
	rm -f main
	rm -f  *.o

	
