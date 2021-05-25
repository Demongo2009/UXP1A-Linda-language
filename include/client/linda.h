//
// Created by bartlomiej on 24.05.2021.
//

#ifndef UXP1A_LINDA_LINDA_H
#define UXP1A_LINDA_LINDA_H

#include "../tuple/Tuple.h"
#include "../tuple/TuplePattern.h"


void linda_output(const Tuple& tuple);
Tuple linda_read(const TuplePattern& pattern, unsigned int timeout = 0);
Tuple linda_input(TuplePattern pattern, unsigned int timeout = 0);

#endif//UXP1A_LINDA_LINDA_H
