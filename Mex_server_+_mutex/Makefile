all: main client server

main: main.o procedure.o
	gcc -o main main.o procedure.o

procedure.o:procedure.c
	gcc -c -g -o procedure.o procedure.c


main.o:main.c
	gcc -c -g -o main.o main.c


client : client.o procedure.o
	gcc -o client client.o procedure.o

server:server.o procedure.o
	gcc -o server server.o procedure.o

client.o:client.c
	gcc -c -g -o client.o client.c

server.o:server.c
	gcc -c -g -o server.o server.c

clean :
	rm -f *.o
	rm -f main client server
