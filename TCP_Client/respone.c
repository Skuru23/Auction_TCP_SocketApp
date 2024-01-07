#include <stdio.h>
#include <stdio.h>

#include "response.h"

void res_code_resolver(int res_code)
{
    switch (res_code)
    {
    // Fof Login
    case LOGINOK:
        printf("Login successfully\n");
        break;
    case ACCBLOCK:
        printf("Account is banned\n");
        break;
    case UNAMENF:
        printf("Account's not found\n");
        break;
    case ALREADYLOGIN:
        printf("Already Login\n");
        break;
    case ACCLOGIN:
        printf("Account is already login in another client\n");
        break;
    case WRONG_PASSWORD:
        printf("Password is wrong\n");
        break;

    // For logout
    case NOTLOGIN:
        printf("You are not logged in\n");
        break;
    case LOGOUTOK:
        printf("Logout successfully\n");
        break;

    // For create Room
    case ROOMCROK:
        printf("Create room successfully\n");
        break;
    case ALREADYEXISTR:
        printf("Room is already exist\n");
        break;
    case ROOMLFULL:
        printf("Server's room list is full, try another time\n");
        break;

    // For join room
    case JOINNOK:
        printf("Join room successfull\n");
        break;
    case ROOMNE:
        printf("Room not exist\n");
        break;
    case ROOMF:
        printf("Room is full\n");
        break;
    case ALREADYINROOM:
        printf("You are already in room\n");
        break;

    // For add item
    case ADDITEMOK:
        printf("Item added successfully\n");
        break;
    case ALREADYEXISTITEM:
        printf("Item is already exist\n");
        break;

        // For bidding

    case BIDOK:
        printf("Auction done\n");
        break;
    case NOTHIGHER:
        printf("This bid is not higher than current bid\n");
        break;
    case NOITEM:
        printf("No item in this room to auction\n");
        break;

    // For buynew
    case BUYOK:
        printf("Buy out successful\n");
        break;

    default:
        printf("Syntax error\n");
        break;
    }
}

void new_item_msg_resolver(char *msg)
{
    char room_name[30], item_name[30];
    int start_bid, direct_sell_price;

    sscanf(msg, "%s %s %d %d", room_name, item_name, &start_bid, &direct_sell_price);
    printf("Room %s: New item arrived!\n", room_name);
    printf("Item %s: Starting bid: %d || Buyout price: %d\n", item_name, start_bid, direct_sell_price);
}

void new_bid_msg_resolver(char *msg)
{
    char room[30], user[30], item[30];
    int bid;
    sscanf(msg, "%s %s %s %d", room, item, user, &bid);
    printf("Room %s: Item %s get new bid from %s\n", room, item, user);
    printf("Current bid for %s is %d\n", item, bid);
}

void sold_msg_resolver(char *msg)
{
    char room_name[30], username[30], item[30];
    sscanf(msg, "%s %s %s", room_name, username, item);
    printf("Room %s: Item %s is sold for %s\n", room_name, item, username);
}

void countdown_msg_resolver(char *msg)
{
    char room[30], item[30];
    int bid, times;

    sscanf(msg, "%s %s %d %d", room, item, &bid, &times);
    printf("Room %s: Countdown for item %s\n", room, item);
    printf("%d time: %d\n", times, bid);
}