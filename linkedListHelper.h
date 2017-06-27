//
// Created by robert on 25/06/17.
//

#ifndef CCOURSEWORK_LINKEDLISTHELPER_H
#define CCOURSEWORK_LINKEDLISTHELPER_H

#include "gameBorad.h"

square * add_To_Start(square *chain_Head, square *new_Square);
void add_To_End(square *chain_Head, square *new_Square);
void add_between(square *before_Square, square *following_Square, square *new_Square);


#endif //CCOURSEWORK_LINKEDLISTHELPER_H
