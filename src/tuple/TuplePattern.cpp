//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "../../include/tuple/TuplePattern.h"
#include "../../include/SerializationUtils.h"

bool TupleElementPattern::checkIfMatch(TupleElement) {
    return false;
}
char *TupleElementPattern::serialize() {
    return nullptr;
}
TupleElementPattern TupleElementPattern::deserialize(std::string content) {
    return TupleElementPattern("");
}

TupleElementPattern::TupleElementPattern(std::string patternElementString) {
    std::string typeStr = SerializationUtils::getNextElementAndErase(patternElementString, ':');
    if (typeStr == "integer") {
        this->valueType = INT;
    } else if (typeStr == "float") {
        this->valueType = FLOAT;
    } else if (typeStr == "string") {
        this->valueType = STRING;
    } else {
        throw std::runtime_error("invalid pattern string - type");
    }

    std::string operatorStr = patternElementString.substr(0, std::min<size_t>(2, patternElementString.size()));

    if (operatorStr == "*") {
        this->matchOperatorType = WHATEVER;
        this->valueToCompare = ""; //in order to not throw exception while printing
    } else {
        if (SerializationUtils::doubleChars.count(operatorStr) != 0) {
            this->matchOperatorType = SerializationUtils::doubleChars[operatorStr];
        } else {
            operatorStr = operatorStr.substr(0, 1);
            if (SerializationUtils::singleChars.count(operatorStr) != 0) {
                this->matchOperatorType = SerializationUtils::singleChars[operatorStr];
            } else {
                throw std::runtime_error("invalid pattern string - operator");
            }
        }

        patternElementString.erase(0, operatorStr.size());
        if (this->valueType == INT) {
            this->valueToCompare = std::stoi(patternElementString);
        } else if (this->valueType == FLOAT) {
            this->valueToCompare = std::stof(patternElementString);
        } else {
            this->valueToCompare = std::move(patternElementString);
        }
    }
}


bool TuplePattern::checkIfMatch(Tuple) {
    return false;
}

char *TuplePattern::serialize() {
    return nullptr;
}

TuplePattern TuplePattern::deserialize(char *) {
    return TuplePattern("");
}

TuplePattern::TuplePattern(std::string patternString) {
    /*
     * przyklad poprawnego - "int:==4, string:>acdfg, float:*"
     *
     * czyli na jeden element sklada sie:
     *  1. typ
     *  2. dwukropek
     *  3. operator porownania
     *  4. wartość, jezeli nie '*' w 3.
     *
     */
    while (!patternString.empty()) {
        std::string elementPatternStr = SerializationUtils::getNextElementAndErase(patternString, ',');
        while(elementPatternStr[0] == ' '){ //get rid of spaces after coma
            elementPatternStr.erase(0, 1);
        }
        this->elementPatterns.emplace_back(TupleElementPattern(elementPatternStr));
    }
}
