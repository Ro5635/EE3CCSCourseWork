//
// This would be far better using C11 generics or an Object Oriented Language where abstract data types can be used...
//

#include "linkedListHelper.h"

/**
 *
 * @param chain_Head
 * @param new_Square
 */
square * add_To_Start(square *chain_Head, square *new_Square){
    new_Square->next_square = chain_Head;
    new_Square->prev_square = NULL;
    chain_Head->prev_square = new_Square;

    //Return the new chain head, it is essential that the caller updates to this
    return new_Square;

}

/**
 *
 * @param chain_Head
 * @param new_Square
 */
void add_To_End(square *chain_Head, square *new_Square){
    //Walk the entire chain and append to end
    square *current_Square = chain_Head;
    while(current_Square->next_square != NULL){
        current_Square = current_Square->next_square;

    }

    //Now at the end square
    current_Square->next_square = new_Square;
    new_Square->prev_square = current_Square;

}

/**
 *  Adds a square to the linked list between two existing squares in the chain
 * @param before_Square
 * @param following_Square
 * @param new_Square
 */
void add_between(square *before_Square, square *following_Square, square *new_Square){

    before_Square->next_square = new_Square;
    new_Square->prev_square = before_Square;
    new_Square->next_square = following_Square;
    following_Square->prev_square = new_Square;
}