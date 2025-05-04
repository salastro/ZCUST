CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -pthread

all: client server

client: client.c helpers.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

server: server.c helpers.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f client server
