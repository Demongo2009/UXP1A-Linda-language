//
// Created by Konrad Kulesza on 19.05.2021.
//

#ifndef UXP1A_LINDA_TUPLE_PATTERN_H
#define UXP1A_LINDA_TUPLE_PATTERN_H

#include "Tuple.h"

class TupleElementPattern {
public:
    TupleElementPattern(std::string);

    bool checkIfMatch(TupleElement);
    char *serialize();
    static TupleElementPattern deserialize(std::string);

    //for debug
    void print(){
        std::cout<<"typ:"<< valueType <<" operator:"<<matchOperatorType<<" wartosc:";
        if (valueType == INT)
            std::cout << std::get<int>(valueToCompare);
        else if (valueType == FLOAT)
            std::cout << std::get<float>(valueToCompare);
        else if (valueType == STRING)
            std::cout << std::get<std::string>(valueToCompare);
    }

private:
    ElemType valueType;
    MatchOperatorType matchOperatorType;
    variant valueToCompare;
};

class TuplePattern {
public:
    TuplePattern(std::string);

    bool checkIfMatch(Tuple);
    char *serialize();
    static TuplePattern deserialize(char *);

    void print(){
        int noOfElements = elementPatterns.size();
        std::cout << "wzorzec " << noOfElements << " elementowy:\n";
        for (int i = 0; i < noOfElements; ++i) {
            std::cout << "\t" << i << ": ";
            elementPatterns[i].print();
            std::cout << std::endl;
        }
    }

private:
    std::vector<TupleElementPattern> elementPatterns;
};


#endif//UXP1A_LINDA_TUPLE_PATTERN_H
