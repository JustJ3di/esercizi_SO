prod_cons: main.o prod_cons.o semafori.o
	gcc -o  prod_cons main.o prod_cons.o semafori.o

main.o: main.c 
	gcc -c -g -o main.o main.c

prod_cons.o: prodcons.c 
	gcc -c -g -o prod_cons.o prodcons.c	

semafori.o: semafori.c semafori.h
	gcc -c -g -o semafori.o semafori.c

clean:
	rm -f *.o
	rm -f prod_cons