//
// Created by robert on 25/06/17.
// Header file for the input handlers
//

#ifndef CCOURSEWORK_INPUTREADHANDLERS_H
#define CCOURSEWORK_INPUTREADHANDLERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Required custom files for operation:
#include "gameBorad.h"

//Buffer size to be used when reading inputs
#define BUFFERSIZE 750

int get_int_from_stdin(int *value);
int get_char_array_from_stdin(char *name);

#endif //CCOURSEWORK_INPUTREADHANDLERS_H
