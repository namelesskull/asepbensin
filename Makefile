
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lmicrohttpd
SRCS=main.c handlers.c html.c file_utils.c

all: server

server:
	rm -f server
	$(CC) $(CFLAGS) $(SRCS) -o server $(LDFLAGS)

clean:
	rm -f server

.PHONY: all clean server

