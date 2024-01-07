#ifndef MSG_H
#define MSG_H


#include "../val/global_var.h"
#include "../model/session_model.h"
#include "../model/room_model.h"

/**
 * Handle receive message from client, recieve message and handle stream, handle request
 *
 * @param sesit: iterator of session in session storage
 *
 * @return :1 if handle success
 *          0 if get an error or connection close
 *
 */
int msg_handle(int sesit);

#endif