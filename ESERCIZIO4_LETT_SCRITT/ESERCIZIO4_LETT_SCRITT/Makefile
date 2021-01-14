all : main lettore_1 scrittore lettore_2

main : main.o semafori.o
	gcc -o main main.o semafori.o

main.o : main.c
	gcc -c -g -o main.o main.c

semafori.o : semafori.c
	gcc -c -g -o semafori.o semafori.c

scrittore : scrittore.o semafori.o
	gcc -o scrittore scrittore.o semafori.o

scrittore.o : scrittore.c
	gcc -c -g -o scrittore.o scrittore.c

lettore_1 : lettore_1.o semafori.o
	gcc -o lettore_1 lettore_1.o semafori.o

lettore_1.o : lettore_1.c
	gcc -c -g -o lettore_1.o lettore_1.c


lettore_2 : lettore_2.o semafori.o
	gcc -o lettore_2 lettore_2.o semafori.o

lettore_2.o : lettore_2.c
	gcc -c -g -o lettore_2.o lettore_2.c


clean : 
	rm -f *.o
	rm -f lettore_1 lettore_2 scrittore main