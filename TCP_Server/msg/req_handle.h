#ifndef REQ_H_H
#define REQ_H_H

#include "../val/global_var.h"
#include "../model/session_model.h"
#include "../model/room_model.h"

/**
 * @function request_handle: handle the request that received from client and send the result code
 *
 * @param sesit: iterator of session in session storage 
 * @param req: request from user
 *
 * @return :1 if success
 *          0 if get an error, client is closed
 */
int request_handle( int sesit, char* req);

#endif