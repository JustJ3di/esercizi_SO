lett_scrit:	main.o lett_scrit.o semafori.o
	gcc -o lett_scrit main.o lett_scrit.o semafori.o

main.o : main.c semafori.h lett_scrit.h
	gcc -c -g -o main.o main.c

semafori.o : semafori.c semafori.h
	gcc -c -g -o semafori.o semafori.c

lett_scrit.o :lett_scrit.c semafori.h lett_scrit.h
	gcc -c -g -o lett_scrit.o lett_scrit.c

