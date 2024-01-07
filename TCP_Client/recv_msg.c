/*TCP Echo Client*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include "recv_msg.h"
#include "response.h"

#define CODE_SIZE 4
#define DELIMITER "\r\n"

void msg_handle(char *msg)
{
    int code;
    if (sscanf(msg, "%d", &code) < 1)
        printf("It's got some bug");
    switch (code)
    {
    case NEWBID:
        new_bid_msg_resolver(msg + (CODE_SIZE + 1));
        break;
    case SOLDED:
        sold_msg_resolver(msg + (CODE_SIZE + 1));
        break;
    case NEWITEMARRIVED:
        new_item_msg_resolver(msg + (CODE_SIZE + 1));
        break;
    case COUNTDOWN:
        countdown_msg_resolver(msg + (CODE_SIZE + 1));
        break;
    default:
        res_code_resolver(code);
        break;
    }
}

void *recv_msg_handle(void *conn_sock)
{
    int sockfd = *((int *)conn_sock);
    pthread_detach(pthread_self());

    // sess[sesit].buff  luu request tach ra tu message
    char *req = (char *)malloc(BUFF_SIZE);
    char *buff = (char *)malloc(BUFF_SIZE * 2);
    char tmp[BUFF_SIZE];
    memset(req, '\0', sizeof(req));
    memset(tmp, '\0', sizeof(tmp));

    while (1)
    {
        int received_bytes = recv(sockfd, req, BUFF_SIZE, 0);
        if (received_bytes < 0)
        {
            perror("\nError4: ");
            pthread_exit(NULL);
        }
        else if (received_bytes == 0)
        {
            printf("Connection closed\n");
            pthread_exit(NULL);
        }

        req[received_bytes] = '\0';
        while (strlen(req) > 0)
        {
            char *part2 = strstr(req, DELIMITER);
            if (part2 == NULL)
            {
                strcat(buff, req);
                break;
            }
            else
            {
                int part2_n = strlen(part2);
                strncat(buff, req, strlen(req) - part2_n);
                printf("%s\n", buff);
                if (strlen(buff) > 0)
                    msg_handle(buff);
                memset(buff, '\0', sizeof(buff));
                memset(tmp, '\0', sizeof(tmp));
                strcpy(tmp, part2 + 2);
                memset(req, '\0', sizeof(req));
                strcpy(req, tmp);
            }
        }
    }
    free(req);
    free(buff);
}