#ifndef BID_H
#define BID_H

/**
 * Start a new auction for first item in queue
 * 
 * @param roomit: iterator of room in room storage
*/
void start_auction(int roomit);

/**
 * Bid to item
 * 
 * @param sesit: iterator of user's session in session store
 * @param bid: bid that user auction
 * 
 * @return : 0 if success,
 *           1 if not logged in, 
 *           2 if not in room,
 *           3 if no item to auction
 *           4 if bid is not higger than current
*/
int bidding(int sesit, int bid);

/**
 * Out buying item
 * 
 * @param sesit: iterator of user's session in session store
 * 
 * @return :0 if buy success,
 *          1 if not logged in, 
 *          2 if not in room,
 *          3 if no item to auction
*/
int buynow(int sesit);

#endif