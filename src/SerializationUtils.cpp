//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "../include/SerializationUtils.h"
#include "../include/consts.h"


std::string SerializationUtils::getNextElementAndErase(std::string &str, char separator) {
    auto idx = str.find(separator);
    if (idx == std::string::npos) {
        idx = str.size();
    }
    std::string contentStr = str.substr(0, idx);
    str.erase(0, idx + 1);
    return std::move(contentStr);
}
stringToOperator SerializationUtils::doubleChars = {
        {"==", EQUAL},
        {">=", GREATER_EQUAL},
        {"<=", LESS_EQUAL}

};

stringToOperator SerializationUtils::singleChars = {
        {">", GREATER},
        {"<", LESS}};