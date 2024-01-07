#ifndef SENDMSG_H
#define SENDMSG_H

#include "../model/room_model.h"
/**
 * @def send_code: send message to client via sockfd
 *
 * @param sockfd: number of socket that use to send message
 * @param res_code: result code of request
 * 
 * @return :1 if success
 *          0 if get an error
 */
int send_code(int sockfd, int res_code);


/**
 * @def send_code: send message to client via sockfd
 *
 * @param conn_sock: number of socket that use to send message
 * @param msg: msg that sent to msg
 * 
 * @return :1 if success
 *          0 if get an error
 */
int send_msg(int conn_sock, char *msg);

void send_roomlist(int sockfd, room roomlist[], int n);

#endif