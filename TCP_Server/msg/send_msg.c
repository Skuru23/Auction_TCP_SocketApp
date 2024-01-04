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
#include "../room/room.h"
#define BUFF_SIZE 1024

/**
 * @def send_msg: send message to client via sockfd
 *
 * @param sockfd: number of socket that use to send message
 * @param res_code: result code of request
 * 
 * @return :1 if success
 *          0 if get an error
 */

int send_msg(int sockfd, int res_code)
{
    char buff[4];
    int sent_bytes, received_bytes;

    memset(buff, '\0', sizeof(buff));
    sprintf(buff, "%d", res_code);

    sent_bytes = send(sockfd, &buff, 4, 0);
    if (sent_bytes < 0)
    {
        perror("\nError6:");
        return 0;
    }
    printf("Sent: %s\n", buff);
    return 1;
}

void send_roomlist(int sockfd, room roomlist[], int n) {
    struct iovec iov[2];

<<<<<<< Updated upstream
    int room_count_buffer;
    iov[0].iov_base = &room_count_buffer;
    iov[0].iov_len = sizeof(int);

    iov[1].iov_base = roomlist;
    iov[1].iov_len = n * sizeof(room);

    writev(sockfd, iov, 2);
}
=======
    room_data roomInfoList[n];
    for (int i = 0; i < n; i++) {
        strncpy(roomInfoList[i].name, roomlist[i].name, 1024);
        roomInfoList[i].userNum = roomlist[i].userNum;
    }

    iov[0].iov_base = roomInfoList;
    iov[0].iov_len = n * sizeof(room_data);

    writev(sockfd, iov, 1);
}
>>>>>>> Stashed changes
