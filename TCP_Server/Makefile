CC = gcc
CFLAGS = -W -pthread

SERVER_SRCS = $(wildcard */*.c)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER = ../server

all: $(SERVER)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SERVER_OBJS) $(TARGET)
runs:
	./server 5551
runc:
	./client 127.0.0.1 5551
test2:
	gcc -pthread tcp_test.c -o test1
	./test1 5550 10
