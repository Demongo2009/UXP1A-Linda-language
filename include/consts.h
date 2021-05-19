//
// Created by Konrad Kulesza on 19.05.2021.
//

#ifndef UXP1A_LINDA_CONSTS_H
#define UXP1A_LINDA_CONSTS_H

#include <variant>
#include <string>

enum ElemType {
    INT,
    FLOAT,
    STRING
};
enum MatchOperatorType {
    WHATEVER,
    EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL
};

typedef std::variant<int, float, std::string> variant;

const int MAX_SIZE_IN_BYTES = 512;
const char Separator = ';';


#endif//UXP1A_LINDA_CONSTS_H
