//
// Created by Konrad Kulesza on 19.05.2021.
//

#ifndef UXP1A_LINDA_TUPLE_PATTERN_H
#define UXP1A_LINDA_TUPLE_PATTERN_H

#include "Tuple.h"

class TupleElementPattern {
public:
    TupleElementPattern(const char*);

    bool checkIfMatch(TupleElement);
    char *serialize();
    static TupleElementPattern deserialize(char *);

private:
    ElemType elemType;
    MatchOperatorType matchOperatorType;
    variant valueToCompare;
};

class TuplePattern {
public:
    TuplePattern(const char*);

    bool checkIfMatch(Tuple);
    char *serialize();
    static TuplePattern deserialize(char *);

private:
    std::vector<TupleElementPattern> elementPatterns;
};


#endif//UXP1A_LINDA_TUPLE_PATTERN_H
