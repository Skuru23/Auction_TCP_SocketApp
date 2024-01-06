CC = gcc
CFLAGS = -W -pthread

SERVER_SRC_DIR = TCP_Server
SERVER_SRCS = $(wildcard $(SERVER_SRC_DIR)/*/*.c)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER = server

all: $(SERVER) makec

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SERVER_OBJS) $(TARGET)
makec:
	gcc TCP_Client/client.c -o client
runs:
	./server 5550
runc:
	./client 127.0.0.1 5550
test2:
	gcc -pthread tcp_test.c -o test1
	./test1 5550 10
