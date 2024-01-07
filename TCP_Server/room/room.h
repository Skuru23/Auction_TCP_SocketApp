#ifndef ROOM_H_H
#define ROOM_H_H

#include "../val/global_var.h"

#include "../model/room_model.h"
#include "../model/session_model.h"

enum RoomStatus
{
    ROOM_OK,
    FULL_ROOM,
    ALREADY_IN_ROOM,
    USER_NOT_LOGINED_IN,
    ROOM_NOT_FOUND,
    UNIDENTIFIED
};

/**
 * Init room_storage
 */
void init_room_store();

/**
 * add room to room_store
 * @param name:room name
 * @param sess: session of user that send create room command
 *
 * @return : room status
 */
enum RoomStatus create_room(char name[], session sess);

/**
 * Join room handle
 *
 * @param room_store: list of room
 * @param room_n: number of room
 * @param room_name: name of room want to join
 * @param sess: session of user use to join room
 * @param sesit: iterator that is index of session in session store
 *
 * @return :0 if OK,
 *          1 if not logged in,
 *          2 if already in room,
 *          3 if room is full,
 *          4 if room is not found
 */
enum RoomStatus join_room(char room_name[], int sesit);
int out_room(int sesit);
#endif
