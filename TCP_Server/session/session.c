#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h>

#include "session.h"
#include "../room/room.h" // test

void init_session_store(){
    for(int i = 0; i<FD_SETSIZE; i++){
        sess_store[i].conn_sock = -1;
    }
    printf("Init session\n");
}

int create_new_session(int conn_sock){
    for(int i=0; i<FD_SETSIZE; i++){
        if(sess_store[i].conn_sock <0){
            sess_store[i].conn_sock = conn_sock;
            sess_store[i].in_room = -1;
            sess_store[i].is_loggedin = 0;
            memset(sess_store[i].username, '\0', sizeof(sess_store[i].username));
            memset(sess_store[i].buff, '\0', sizeof(sess_store[i].buff));
            return i;
        }
    }
    return -1;
}