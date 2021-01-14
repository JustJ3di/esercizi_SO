all:main studente docente

main.o:main.c
	gcc -c -g -o main.o main.c

studente.o:studente.c
	gcc -c -g -o studente.o studente.c

procedure.o:procedure.c
	gcc -c -g -o procedure.o procedure.c

docente.o:docente.c
	gcc -c -g -o docente.o docente.c


main: main.o procedure.o
	gcc -o main main.o procedure.o

studente:studente.o procedure.o
	gcc -o studente studente.o procedure.o

docente:docente.o procedure.o
	gcc -o docente docente.o procedure.o

clean:
	rm -f main docente studente
	rm -f *.o