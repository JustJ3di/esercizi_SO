all:main server client

main:main.c
	gcc -o main main.c

server:main_server.c
	gcc -o server main_server.c -lpthread

client:main_client.c
	gcc -o client main_client.c

clean:
	rm -f main_client main main_server
