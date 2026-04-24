CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lmicrohttpd

SRCS = main.c handlers.c html.c file_utils.c
OBJS = $(SRCS:.c=.o)
BIN = server

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c handlers.h
handlers.o: handlers.c handlers.h html.h file_utils.h
html.o: html.c html.h file_utils.h
file_utils.o: file_utils.c file_utils.h

clean:
	rm -f $(BIN) $(OBJS)

.PHONY: all clean
