#ifndef SESSION_H
#define SESSION_H

#define BUFF_SIZE 1024

typedef struct session
{
    int conn_sock;
    char username[30];
    int in_room;
    int is_loggedin;
}session;

#endif