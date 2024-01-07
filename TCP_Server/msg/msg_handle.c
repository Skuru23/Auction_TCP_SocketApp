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

#include "req_handle.h"
#include "msg_handle.h"

#define BUFF_SIZE 1024
#define DELIMITER "\r\n"

int msg_handle(int sesit)
{
    // sess[sesit].buff  luu request tach ra tu message
    char *req = (char *)malloc(BUFF_SIZE);
    char tmp[BUFF_SIZE];
    memset(req, '\0', sizeof(req));
    memset(tmp, '\0', sizeof(tmp));

    int received_bytes = recv(sess_store[sesit].conn_sock, req, BUFF_SIZE, 0);
    if (received_bytes < 0)
    {
        perror("\nError4: ");
        return 0;
    }
    else if (received_bytes == 0)
    {
        printf("Connection closed\n");
        return 0;
    }

    req[received_bytes] = '\0';
    while (strlen(req) > 0)
    {
        char *part2 = strstr(req, DELIMITER);
        if (part2 == NULL)
        {
            strcat(sess_store[sesit].buff, req);
            break;
        }
        else
        {
            int part2_n = strlen(part2);
            strncat(sess_store[sesit].buff, req, strlen(req) - part2_n);
            printf("%d: %s\n", sess_store[sesit].conn_sock, sess_store[sesit].buff);
            if (strlen(sess_store[sesit].buff) > 0)
            {
                if (!request_handle(sesit, sess_store[sesit].buff))
                {
                    return 0;
                }
            }
            memset(sess_store[sesit].buff, '\0', sizeof(sess_store[sesit].buff));
            memset(tmp, '\0', sizeof(tmp));
            strcpy(tmp, part2 + 2);
            memset(req, '\0', sizeof(req));
            strcpy(req, tmp);
        }
    }
    free(req);
    return 1;
}
