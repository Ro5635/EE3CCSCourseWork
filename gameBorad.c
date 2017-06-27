//
// Created by robert on 22/06/17.
// This holds the functions responsible for manipulating a game board of snakes and ladders
// Additional functionality can be added to the squares by using the square struct.

#include "gameBorad.h"

action * get_New_Action(int destination_Square_No, action_Types action_Type ){

    action * new_Action = (struct action*) malloc(sizeof(struct action));
    //Apply data
    new_Action->action_type = action_Type;
    new_Action->destination_Square_No = destination_Square_No;
    return new_Action;

}

/**
 *
 *
 * When called with NULL as the pre_square this will create an isolated square that is not in a data structure
 * @return
 */
square * get_New_Square(int square_num, square *prev_square, action *squares_action){

    square *new_square = (struct square*) malloc(sizeof(struct square));

    //Apply the data
    new_square->no = square_num;
    new_square->prev_square = prev_square;
    //Pre-load the next square as NULL
    new_square->next_square = NULL;
    new_square->action = squares_action;

    return new_square;

}

/**
 * Creates a new empty game board, the squares are not initilised and the squares data structure is Null
 * @return
 */
board * get_New_Board(){

    //Create a new Game Board
    board *new_board = (struct board*) malloc(sizeof(struct board));
    new_board->action_Squares_Head = NULL;
    new_board->action_Squares_Tail = NULL;

    return new_board;

}

board_Print_Data * get_New_Board_Print_Structure(){
    board_Print_Data * new_board_data = (struct board_Print_Data*) malloc(sizeof(struct board_Print_Data));
    new_board_data->game_board = NULL;
    new_board_data->ptr_To_Square = NULL;
    new_board_data->index = 0;
    new_board_data->line_Length = 0;


    return new_board_data;

}

/**
 *
 * @param existing_Board
 * @param new_Square
 * @return
 */
void * add_New_Square_To_Board(board *existing_Board, square *new_Square){
    //The new square needs to be added in the correct location, this requires walking through the array to the
    //correct position before insertion

    if(existing_Board->action_Squares_Head != NULL) {

        square *current_Square = existing_Board->action_Squares_Head;

        //check new square is not smaller than the first element in the list
        if(new_Square->no < current_Square->no){
            //add before current square
            existing_Board->action_Squares_Head = add_To_Start(current_Square, new_Square);

        }else {

            while (new_Square->no > current_Square->no && current_Square->next_square != NULL) {
                current_Square = current_Square->next_square;
            }

                //Not the last Square
            if (current_Square->next_square != NULL) {
                add_between(current_Square->prev_square, current_Square, new_Square);

            } else {
                //The Last Square
                add_To_End(current_Square, new_Square);
            }
        }



    }else{
        //It is the first square on the board!
        existing_Board->action_Squares_Head = new_Square;
    }



}


/**
 * Displays a square to the std Out stream
 * @param aSquare
 */
void print_Square(square *aSquare){
    if(aSquare->action != NULL){
        //Ensure it is a printed type of action
        if(aSquare->action->action_type != ENDOFBOARD){
            printf("[%d->%d]\t", aSquare->no, aSquare->action->destination_Square_No);
        }else{
            //Print in normal format
            printf("[%d]\t", aSquare->no);
        }

    }else{
        printf("[%d]\t", aSquare->no);
    }

}


/**
 * Displays a square to the std Out stream
 * @param square_Num
 */
void int_print_Square(int square_Num){
    printf("[%d]\t", square_Num);
}

/**
 * Prints a row Forwards
 * @param game_board
 * @param action_Square_Pointer
 * @param current_Index
 * @return
 */
void print_Forward_Row(board_Print_Data *board_Data){

    int line_Length = board_Data->game_board->xMax;
    int current_Line_End = board_Data->index + 1;
    int internal_Index = board_Data->index - (line_Length - 1);

    //Get a pointer to the first action_square for this row
    while(board_Data->ptr_To_Square->prev_square != NULL){
        if(board_Data->ptr_To_Square->prev_square->no  >= internal_Index ){
            board_Data->ptr_To_Square = board_Data->ptr_To_Square->prev_square;
        }else{
            break;
        }

    }

    //store current square pointer state
    square *tmp_ptr_To_Square = board_Data->ptr_To_Square;

    while(internal_Index < current_Line_End){

        if(tmp_ptr_To_Square->no != internal_Index){
            //print the normal square
            int_print_Square(internal_Index);
        }else{
            //print the action square
            print_Square(tmp_ptr_To_Square);
            //move the list on one
            if(tmp_ptr_To_Square->next_square != NULL){
                tmp_ptr_To_Square = tmp_ptr_To_Square->next_square;
            }

        }

        internal_Index++;

    }

    board_Data->index = board_Data->index - line_Length;

    //Ensure that the pointer for the action square is correctly positioned
    while(board_Data->ptr_To_Square->no >= (current_Line_End - line_Length)){
        if(board_Data->ptr_To_Square->prev_square != NULL){
            board_Data->ptr_To_Square = board_Data->ptr_To_Square->prev_square;
        }else{
            break;
        }

    }

    //Print new line
    printf("\n");

}

/**
 * Prints a row backwards
 * @param game_board
 * @param action_Square_Pointer
 * @param current_Index
 * @return
 */
void print_Backward_Row(board_Print_Data *board_Data){

    int line_Length = board_Data->game_board->xMax;
    int current_Line_End = board_Data->index - line_Length;

    while(board_Data->index > current_Line_End){

        if(board_Data->ptr_To_Square->no != board_Data->index){
            //print the normal square
            int_print_Square(board_Data->index);
        }else{
            //print the action square
            print_Square(board_Data->ptr_To_Square);
            //move the list on one
            if(board_Data->ptr_To_Square->prev_square != NULL){
                board_Data->ptr_To_Square = board_Data->ptr_To_Square->prev_square;
            }

        }

        board_Data->index--;

    }

    //Print new line
    printf("\n");
}

/**
 * Prints out the supplied game borad to the standard output stream
 * @param game_board
 */
void print_Game_Board(board *game_board){
    //Draw full board to the screen:

    //Get a new board print data structure
    board_Print_Data *board_Data = get_New_Board_Print_Structure();

    //Populate the data structure
    board_Data->index = game_board->nMax;
    board_Data->line_Length = game_board->xMax;
    board_Data->game_board = game_board;


    board_Data->ptr_To_Square = game_board->action_Squares_Head;
    //Move to end of the list
    while(board_Data->ptr_To_Square->next_square != NULL){
        board_Data->ptr_To_Square = board_Data->ptr_To_Square->next_square;

    }

    //Squares have even number of rows!
    for (int i = 0; i < (game_board->yMax/2); ++i) {
        print_Backward_Row(board_Data);
        print_Forward_Row(board_Data);

    }

    //Release the memory used by the game_board_data structure
    free(board_Data);


}

/**
 *
 */
void test_Square_Structure(){
    //make a board:
    board *game_board = get_New_Board();

    square *firstSquare = (struct square*) malloc(sizeof(struct square));

    //add the start of the chain to the game board
    game_board->action_Squares_Head = firstSquare;

    //Check that the head has been linked correctly:
    if(firstSquare != game_board->action_Squares_Head){
        printf("Error: Head of linked list does not match the head\n");
    }

    //Check that the tail has been linked correctly:
    if(NULL != game_board->action_Squares_Tail){
        printf("Error: The head of the linked list's prev square is not NULL\n");
    }

    game_board->action_Squares_Head->no = 7557;

    //Just make a action for use in satisfying the signature for this test
    action * new_action = get_New_Action(44, LADDER);

    game_board->action_Squares_Head->next_square = get_New_Square(44, game_board->action_Squares_Head, new_action);

    //Set the first one indirectly to test the prev functionality:
    game_board->action_Squares_Head->next_square->prev_square->no = 55;

    if(firstSquare->no != 55){
        printf("Error: Issue with tracking back up Square Linked list");
        exit(1);
    }

    if(firstSquare->next_square->no != 44){
        printf("Error: Issue with getting the value from the next square in the linked list");
        exit(1);
    }

}