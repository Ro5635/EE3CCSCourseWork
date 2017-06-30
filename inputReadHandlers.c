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
