all:main visualizzatore

main:main.o procedure.o
	gcc -o main main.o procedure.o

main.o : main.c 
	gcc -c -g -o main.o main.c

procedure.o:procedure.c
	gcc -c -g -o procedure.o procedure.c

visualizzatore: visualizzatore.o procedure.o
	gcc -o visualizzatore visualizzatore.o procedure.o

visualizzatore.o: visualizzatore.c
	gcc -c -g -o visualizzatore.o visualizzatore.c

clean:
	rm -f *.o
	rm -f visualizzatore main
	ipcrm -a