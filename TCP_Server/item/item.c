#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "item.h"
#include "../bid/bid.h"

/***
 * Create new item node for item queue
 *
 * @param name: name of item
 * @param owner: session index of client
 * @param start_bid: starting price
 * @param direct_sell_price: buyout price
 *
 * @return :pointer of item node
 */
item *create_item_node(char name[], int owner, int start_bid, int direct_sell_price)
{
    item *node = (item *)malloc(sizeof(item));
    strcpy(node->name, name);
    node->owner = owner;
    node->current_bid = start_bid;
    node->best_cus = -1;
    node->direct_sell_price = direct_sell_price;
    node->next = NULL;
    return node;
}

/**
 * push item to item queue
 *
 * @param queue: item queue
 * @param it: pointer of item
 */
void push_item(item **queue, item *it)
{
    if (*queue == NULL)
    {
        *queue = it;
    }
    else
    {
        push_item(&((*queue)->next), it);
    }
}

/**
 * Delete item from queue
 *
 * @param queue: item queue
 * @param name: name of item
 *
 * @return :1 if delete successful, 0 if not found
 */
int delete_item(item **queue, char name[])
{
    item *current = *queue;
    item *prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                (*queue) = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

int pop_item(item **queue)
{
    return delete_item(queue, (*queue)->name);
}

/**
 * check item is existt in queue or not
 *
 * @param queue: item queue
 * @param item_name: name of item
 *
 * @return :0 if not found
 *          1 if found
 */
int find_item(item *queue, char item_name[])
{
    item *i = queue;
    while (i != NULL)
    {
        if (strcmp(i->name, item_name) == 0)
            return 1;
        i = i->next;
    }
    return 0;
}

int addItem(char name[], int start_bid, int direct_sell_price, int sesit)
{
    if (!sess_store[sesit].is_loggedin)
        return 1;
    if (sess_store[sesit].in_room == -1)
        return 2;
    if (find_item(room_store[sess_store[sesit].in_room].item_queue, name))
        return 3;
    item *new_item = create_item_node(name, sesit, start_bid, direct_sell_price);
    pthread_mutex_lock(&room_mutex);
    push_item(&(room_store[sess_store[sesit].in_room].item_queue), new_item);
    pthread_mutex_unlock(&room_mutex);
    if (room_store[sess_store[sesit].in_room].item_queue->next == NULL)
    {
        start_auction(sess_store[sesit].in_room);
    }
    return 0;
}