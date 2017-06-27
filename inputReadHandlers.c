//
// Responsible for handling the reading from the standard input stream
//

#include "inputReadHandlers.h"

/**
 *  Reads an int from the buffer
 * @param buffer
 * @param value
 * @return
 */
int get_int_From_Buffer(char *buffer, int *value){
    return sscanf(buffer, "%d", value);

}


/**
 * Attempts to get an int from the user, if there is some error then returns -1,
 * if the user inputs -1 then you also get -1...
 * @param value a pointer to the value you wish to fill
 * @return returns 1 on success; or -1 if error
 */
int get_int_from_stdin(int *value){
    char buffer[BUFFERSIZE];   //The buffer to be used for the reading

    fgets(buffer, sizeof(buffer), stdin);   //This reads in to the buffer from stdin
    //We now use sscanf to get the value as an integer
    if(1 == get_int_From_Buffer(buffer, value)){
        //It is safe to use value
        return 1;
    }else{
        return 0;
    }
}

/**
 * Gets a char array from the stdin
 * @param name the char array for which the data should be inserted
 * @return
 */
int get_char_array_from_stdin(char *name){
    static char buffer[BUFFERSIZE]; //Allocate the space from compile; don't keep re-allocating this

    fgets(buffer, sizeof(buffer), stdin);

    //This is likely copying all of the empty buffer as well...?
    strcpy(name, buffer);

    //remove the new line from the (almost) end of the array
    if(name[(sizeof(name) - 2)] == '\n'){
        name[(sizeof(name) - 2)] = '\0';//Memory leak...?
    }


}


/**
 *  Interperets the game board file and returns a square containing an action
 * @param line
 * @return
 */
square * interpert_Game_Board_File_Line(char *line){
    int first_Num;
    int second_Num;

    //deliminator for splitting up input
    const char s = ' ';
    char *token;

    /* get the first token */
    token = strtok(line, &s);

    if(token != NULL){
        get_int_From_Buffer(token, &first_Num);
    }else{
        //Error in the file format
        printf("Syntax Error In File, There should be two numbers per line");
        exit(1);
    }

    //Get the next token
    token = strtok(NULL, &s);

    if(token != NULL){
        get_int_From_Buffer(token, &second_Num);
    }else{
        //Error in the file format
        printf("Syntax Error In File, There should be two numbers per line. The second number was not present.");
        exit(1);

    }

    //Ensure that the second number is smaller than the first
    if(first_Num <= second_Num){
        //Error state, the second number must be smaller
        printf("Error In File, the second number must be smaller!");
        exit(1);

    }

    //Build the new action
    action * new_action;

    //Check it is not the end of the file
    if(second_Num != 0) {

        //If the second number is negative then it is a snake, the action should then be displayed on the first number
        if (second_Num < 0) {
            //Its a snake!, second_Num is negative, *-1 to make positive
            second_Num = second_Num * -1;
            new_action = get_New_Action(second_Num, SNAKE);
            //Return an isolated square
            return get_New_Square(first_Num, NULL, new_action);

        } else {
            //It's a Ladder
            new_action = get_New_Action(first_Num, LADDER);
            //Return an isolated square
            return get_New_Square(second_Num, NULL, new_action);

        }
    }else{
        //It is the end of the file
        new_action = get_New_Action(0, ENDOFBOARD);
        //return the isolated square
        return get_New_Square(first_Num, NULL, new_action);

    }


}