//
// Created by Konrad Kulesza on 19.05.2021.
//

#ifndef UXP1A_LINDA_SERIALIZATIONUTILS_H
#define UXP1A_LINDA_SERIALIZATIONUTILS_H

#include "consts.h"
#include <map>

typedef std::map<std::string, MatchOperatorType> stringToOperator;

class SerializationUtils {
public:
    static std::string getNextElementAndErase(std::string &, char separator = Separator);
    static stringToOperator singleChars;
    static stringToOperator doubleChars;
};

#endif//UXP1A_LINDA_SERIALIZATIONUTILS_H
