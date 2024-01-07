#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "room.h"

void init_room_store()
{
    for (int i = 0; i < ROOM_NUM; i++)
    {   
        memset(room_store[i].name, '\0', ROOM_NAME_MAX_LENGTH);
        room_store[i].item_queue = NULL;
        room_store[i].userNum = -1;
        for (int j = 0; j < 30; j++)
        {
            room_store[i].userList[j] = -1;
        }
    }
    printf("Init room\n");
}

/***
 * find room by name in room storage
 * 
 * @param room_name: name of room to find
 * 
 * @return :i index of this room in room storage
 *          -1 if not found
*/
int findRoom(char room_name[])
{
    for (int i = 0; i < ROOM_NUM; i++)
    {
        if (!strcmp(room_store[i].name, room_name))
        {
            return i;
        }
    }
    return -1;
}

enum RoomStatus create_room(char name[], session sess)
{
    if (!sess.is_loggedin)
        return USER_NOT_LOGINED_IN;
    if (findRoom(name) != -1)
        return ALREADY_IN_ROOM;

    for (int i = 0; i < ROOM_NUM; i++)
    {
        if (room_store[i].userNum == -1)
        {
            room_store[i].userNum = 0;
            strncpy(room_store[i].name, name, 30);
            printf("Create success\n");
            return ROOM_OK;
        }
    }
    return FULL_ROOM;
}

enum RoomStatus join_room(char room_name[], int sesit)
{
    if (!sess_store[sesit].is_loggedin)
    {
        return USER_NOT_LOGINED_IN;
    }

    if (sess_store[sesit].in_room != -1)
    {
        return ALREADY_IN_ROOM;
    }

    int it = findRoom(room_name);
    if (it == -1){
        printf("Room not found\n");
        return ROOM_NOT_FOUND;
    }

    if (room_store[it].userNum == ROOM_NUM)
        return FULL_ROOM;

    for (int i = 0; i < ROOM_NUM; i++)
    {
        if (room_store[it].userList[i] == -1)
        {
            room_store[it].userNum++;
            room_store[it].userList[i] = sesit;
            sess_store[sesit].in_room = it;
            printf("Join success:%d|%d\n", room_store[it].userNum, it);
            return ROOM_OK;
        }
    }

    return UNIDENTIFIED;
}

int out_room(int sesit){
    if (!sess_store[sesit].is_loggedin)
        return 2; // accout not login
    if (sess_store[sesit].in_room == -1)
        return 3; // account not in room
    room_store[sess_store[sesit].in_room].userNum--;
    for (int i = 0; i < ROOM_NUM; i++)
    {
        if(room_store[sess_store[sesit].in_room].userList[i] == sesit) {
            room_store[sess_store[sesit].in_room].userList[i] = -1;
            break;
        }
    }
    sess_store[sesit].in_room = -1;
    return 1; // account out room success
    
}
