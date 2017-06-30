#include <stdio.h>
#include <stdlib.h>
#include "gameBorad.h"
#include <math.h>


int main() {

    //Test the square structure, if a test fails the program will exit with a debug message.
    test_Square_Structure();

    //make a board:
    board *game_board = get_New_Board();

    //Instruct the user
    printf("Enter the values from the file one line at a time, OR Pipe in the file from CMD! : \n");

    //Get all of the squares with an action from the user
    char new_Line;
    square * new_square = NULL;

    //Read from the input until the end of board is detected
    do{
        //read the newest line
        get_char_array_from_stdin(&new_Line);
        //interpret the line
        new_square = interpert_Game_Board_File_Line(&new_Line);
        //add the square to the board
        add_New_Square_To_Board(game_board, new_square);
    }while(new_square->action->action_type != ENDOFBOARD);


    //Extract limit data from the end square, it is assumed boards all are square:
    double sqrt_Of_Max_Square = sqrt(new_square->no);

    //If it is not a square then exit with debug message.
    if(fmod(sqrt_Of_Max_Square, 1) != 0){
        //It's not a square board!
        //This is an exit condition!
        printf("The board is not square. Exiting.");
        exit(1);
    }

    //It is known that this is safe as above passed
    game_board->xMax = (int) sqrt_Of_Max_Square;
    game_board->yMax = (int) sqrt_Of_Max_Square;
    game_board->nMax = new_square->no;


    //Print the board out to the terminal
    print_Game_Board(game_board);

    //Release Memory
    free(game_board);
    free(new_square);


    //Done
    exit(0);

}