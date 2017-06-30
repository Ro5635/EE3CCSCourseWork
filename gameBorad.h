//
// Created by robert on 25/06/17.
//

#ifndef CCOURSEWORK_GAMEBORAD_H
#define CCOURSEWORK_GAMEBORAD_H


/**
 *  Defines the action types that a square can be, includes ENDOFBOARD, this is used to act appropiatly (win) when the
 *  user reaches it.
 */
typedef enum action_Types { SNAKE , LADDER, ENDOFBOARD} action_Types;

/**
 *
 */
typedef struct action{
    int destination_Square_No;
    enum action_Types action_type;
} action;


/**
 *  Represents a square on teh board, has attributes such as square number.
 */
typedef struct square{
    int no;
    struct square *next_square;
    struct square *prev_square;
    struct action *action;

} square;

/**
 * There is room here for this to be extended to hold further details such as colour about the square
 */
typedef struct board{
    int xMax;
    int yMax;
    int nMax;
    square *action_Squares_Head;
    square *action_Squares_Tail;

} board;

/**
 * Data structure used to hold the attributes needed in printing out the board
 */
typedef struct board_Print_Data{
    int index;
    int line_Length;
    square *ptr_To_Square;
    board *game_board;

} board_Print_Data;

action * get_New_Action(int destination_Square_No, action_Types action_Type );
square * get_New_Square(int square_num, square *prev_square, action *squares_action);
board * get_New_Board();
board_Print_Data * get_New_Board_Print_Structure();
void * add_New_Square_To_Board(board *existing_Board, square *new_Square);
void print_Square(square *aSquare);
void int_print_Square(int square_Num);
void print_Forward_Row(board_Print_Data *board_Data);
void print_Backward_Row(board_Print_Data *board_Data);
void print_Game_Board(board *game_board);
square * interpert_Game_Board_File_Line(char *line);

//Unit Tests
void test_Square_Structure();

#include <stdio.h>
#include <stdlib.h>
#include "linkedListHelper.h"
#include "inputReadHandlers.h"


#endif //CCOURSEWORK_GAMEBORAD_H
