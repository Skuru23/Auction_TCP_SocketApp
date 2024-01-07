#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <errno.h>

#include "send_msg.h"
#include "../room/room.h"
#define BUFF_SIZE 1024
#define CODE_SIZE 4

int send_code(int sockfd, int res_code)
{
    char buff[CODE_SIZE + 2];
    int sent_bytes, received_bytes;

    memset(buff, '\0', sizeof(buff));
    sprintf(buff, "%d\r\n", res_code);

    sent_bytes = send(sockfd, &buff, strlen(buff), 0);
    if (sent_bytes < 0)
    {
        perror("\nError6:");
        return 0;
    }
    printf("Sent: %s\n", buff);
    return 1;
}

int send_msg(int sockfd, char *msg){
    char buff[BUFF_SIZE];
    strcpy(buff, msg);
    strcat(buff, "\r\n\0");
    int sent_bytes = send(sockfd, &buff, strlen(buff), 0);
    if (sent_bytes < 0)
    {
        perror("\nError6:");
        return 0;
    }
    printf("Sent: %s\n", buff);
    return 1;
}

void send_roomlist(int sockfd, room roomlist[], int n) {

}

// void recv_roomlist(int sockfd, room roomlist[], int *n) {
//     struct iovec iov[2];

//     int room_count_buffer;
//     iov[0].iov_base = &room_count_buffer;
//     iov[0].iov_len = sizeof(int);

//     iov[1].iov_base = roomlist;
//     iov[1].iov_len = *n * sizeof(room);

//     readv(sockfd, iov, 2);

//     *n = room_count_buffer;
// }

