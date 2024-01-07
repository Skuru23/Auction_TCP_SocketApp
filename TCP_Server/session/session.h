#ifndef SESS_HANDLE_H
#define SESS_HANDLE_H

#include "../model/session_model.h"
#include "../val/global_var.h"

/**
 * Init session store
 * 
*/
void init_session_store();

/**
 * create new session to session storage when new client connect to
 * 
 * @param conn_sock: socket number of new client
 * 
 * @return :i index of new session in sess_store,
 *          -1 if sess_store is full
*/
int create_new_session(int conn_sock);

#endif