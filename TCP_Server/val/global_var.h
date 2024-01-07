#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <pthread.h>

#include "../model/room_model.h"
#include "../model/session_model.h"

#define ROOM_NUM 30                 // Max num of room

extern pthread_mutex_t room_mutex;  // mutex to lock and unlock resouces for aution and item adding
extern session *sess_store;         // session storage for all module can use
extern room *room_store;            // room storage for all module can use

#endif