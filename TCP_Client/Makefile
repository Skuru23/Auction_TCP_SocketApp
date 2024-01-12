CC = gcc
CFLAGS = -pthread

CLIENT_SRCS = $(wildcard *.c)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT = ../client

all: $(CLIENT)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(CLIENT_OBJS) $(TARGET)
runs:
	./server 5551
runc:
	./client 127.0.0.1 5551
test2:
	gcc -pthread tcp_test.c -o test1
	./test1 5550 10
