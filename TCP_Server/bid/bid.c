#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "bid.h"
#include "../val/global_var.h"
#include "../val/response.h"
#include "../item/item.h"
#include "../msg/send_msg.h"

#define EXTENDSTIME 30
#define EXTENDSTIME2 30
#define INCREMENTSTEP 10

/**
 * Annouce to all user in room
 *
 * @param room_it: iterator of room in room storage
 * @param msg: message use to annouce
 * @param anno_type: annoucement type
 */
void room_anno(int room_it, char *msg);

char anno_msg[BUFF_SIZE];

/**
 * start an auction
 *
 */
void *auction_start(void *roomit)
{
    pthread_detach(pthread_self());
    printf("lmao5\n");
    int it = *((int *)roomit);
    printf("Room %d: %s start auction\n", it, (room_store[it].item_queue)->name);

    // Send annocement to all user in room
    if (room_store[it].item_queue->best_cus == -1)
    {
        memset(anno_msg, '\0', BUFF_SIZE);
        sprintf(anno_msg, "%d %s %s %d %d",
                NEWITEMARRIVED,
                room_store[it].name,
                room_store[it].item_queue->name,
                room_store[it].item_queue->current_bid,
                room_store[it].item_queue->direct_sell_price);
        room_anno(it, anno_msg);
    }

    // Start time counter
    sleep(EXTENDSTIME);

    // End time counter start countdown pharse
    for (int i = 0; i < 3; i++)
    {
        // Send annoucement to all user in room
        memset(anno_msg, '\0', BUFF_SIZE);
        sprintf(anno_msg, "%d %s %s %d %d",
                COUNTDOWN,
                room_store[it].name,
                room_store[it].item_queue->name,
                room_store[it].item_queue->current_bid,
                i + 1);
        room_anno(it, anno_msg);

        sleep(EXTENDSTIME2);
    }

    // Result of auction
    if (room_store[it].item_queue->best_cus == -1)
    {
        printf("Outbid\n");
    }
    else
    {
        memset(anno_msg, '\0', BUFF_SIZE);
        sprintf(anno_msg, "%d %s %s %s",
                SOLDED,
                room_store[it].name,
                sess_store[room_store[it].item_queue->best_cus].username,
                room_store[it].item_queue->name);
        room_anno(it, anno_msg);
        printf("Item sold to %s\n", sess_store[room_store[it].item_queue->best_cus].username);
    }

    // Auction done pop item from queue
    pthread_mutex_lock(&room_mutex);
    pop_item(&(room_store[it].item_queue));
    pthread_mutex_unlock(&room_mutex);

    // Check queue and start new auction for next item
    if (room_store[it].item_queue != NULL)
        auction_start(roomit);
    else
        pthread_exit(NULL);
}

void start_auction(int roomit)
{

    int *it = malloc(sizeof(int));
    if (it == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for thread argument\n");
        exit(EXIT_FAILURE);
    }

    *it = roomit;
    printf("Auction start for %s in room %d\n", (room_store[*it].item_queue)->name, *it);
    pthread_create(&(room_store[roomit].time_counter), NULL, &auction_start, it);
}

int bidding(int sesit, int bid)
{
    // Check user state
    if (!sess_store[sesit].is_loggedin)
        return 1;
    if (sess_store[sesit].in_room == -1)
        return 2;
    if (room_store[sess_store[sesit].in_room].item_queue == NULL)
        return 3;

    // Check bid
    if (bid - INCREMENTSTEP < room_store[sess_store[sesit].in_room].item_queue->current_bid)
        return 4;
    pthread_cancel(room_store[sess_store[sesit].in_room].time_counter);

    // If bid is higher than buy out price
    if (bid >= room_store[sess_store[sesit].in_room].item_queue->direct_sell_price)
    {
        memset(anno_msg, '\0', BUFF_SIZE);
        sprintf(anno_msg, "%d %s %s %s",
                SOLDED,
                room_store[sess_store[sesit].in_room].name,
                sess_store[sesit].username,
                room_store[sess_store[sesit].in_room].item_queue->name);
        room_anno(sess_store[sesit].in_room, anno_msg);

        printf("Item sold to %s\n", sess_store[sesit].username);
        pop_item(&(room_store[sess_store[sesit].in_room].item_queue));
        if (room_store[sess_store[sesit].in_room].item_queue != NULL)
            start_auction(sess_store[sesit].in_room);
        send_code(sess_store[sesit].conn_sock, BIDOK);
    }
    else
    {
        room_store[sess_store[sesit].in_room].item_queue->best_cus = sesit;
        room_store[sess_store[sesit].in_room].item_queue->current_bid = bid;
        start_auction(sess_store[sesit].in_room);

        memset(anno_msg, '\0', BUFF_SIZE);
        sprintf(anno_msg, "%d %s %s %s %d\r\n",
                NEWBID,
                room_store[sess_store[sesit].in_room].name,
                room_store[sess_store[sesit].in_room].item_queue->name,
                sess_store[sesit].username,
                bid);
        room_anno(sess_store[sesit].in_room, anno_msg);
        send_code(sess_store[sesit].conn_sock, BIDOK);
    }
    return 0;
}

int buynow(int sesit)
{
    // Check user state
    if (!sess_store[sesit].is_loggedin)
        return 1;
    if (sess_store[sesit].in_room == -1)
        return 2;
    if (room_store[sess_store[sesit].in_room].item_queue == NULL)
        return 3;

    // Buy out handle
    pthread_cancel(room_store[sess_store[sesit].in_room].time_counter);

    // Annouce to all user
    memset(anno_msg, '\0', BUFF_SIZE);
    sprintf(anno_msg, "%d %s %s %s",
            SOLDED,
            room_store[sess_store[sesit].in_room].name,
            sess_store[sesit].username,
            room_store[sess_store[sesit].in_room].item_queue->name);
    room_anno(sess_store[sesit].in_room, anno_msg);

    printf("Item sold to %s\n", sess_store[sesit].username);
    pop_item(&(room_store[sess_store[sesit].in_room].item_queue));

    // start new auction
    if (room_store[sess_store[sesit].in_room].item_queue != NULL)
        start_auction(sess_store[sesit].in_room);
    send_code(sess_store[sesit].conn_sock, BUYOK);

    return 0;
}

void room_anno(int room_it, char *msg)
{
    if (room_store[room_it].userNum < 0)
        return;
    strcat(msg, "\r\n\0");
    for (int i = 0; i < ROOM_SIZE; i++)
    {
        if (room_store[room_it].userList[i] >= 0)
        {
            send_msg(sess_store[room_store[room_it].userList[i]].conn_sock, msg);
        }
    }
}