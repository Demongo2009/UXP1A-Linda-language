//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "../../include/tuple/TuplePattern.h"
#include "../../include/SerializationUtils.h"
#include <cstring>
#include <sstream>

bool TupleElementPattern::checkIfMatch(TupleElement) {
    return false;
}

std::string TupleElementPattern::serialize() {
    std::stringstream buffer;
    ElemType type = this->valueType;
    buffer << type << Separator;
    buffer << this->matchOperatorType << Separator;
    if (this->matchOperatorType == WHATEVER) {
        return buffer.str();//do not serialize value
    }

    if (type == INT)
        buffer << std::get<int>(this->valueToCompare);
    else if (type == FLOAT)
        buffer << std::get<float>(this->valueToCompare);
    else if (type == STRING)
        buffer << std::get<std::string>(this->valueToCompare);
    else
        throw std::runtime_error("niepoprawny rodzaj wartosci w serialziacji elementu");
    buffer << Separator;
    return buffer.str();
}
TupleElementPattern TupleElementPattern::deserialize(std::string &content) {
    std::string utilStr = SerializationUtils::getNextElementAndErase(content);
    auto type = (ElemType) std::stoi(utilStr);
    utilStr = SerializationUtils::getNextElementAndErase(content);
    auto matchOperator = (MatchOperatorType) std::stoi(utilStr);

    if(matchOperator == WHATEVER){
        return TupleElementPattern(type, matchOperator, "");
    }

    utilStr = SerializationUtils::getNextElementAndErase(content);
    if (type == INT) {
        int value = std::stoi(utilStr);
        return TupleElementPattern(type, matchOperator, value);
    } else if (type == FLOAT) {
        float value = std::stof(utilStr);
        return TupleElementPattern(type, matchOperator, value);
    } else if (type == STRING) {
        return TupleElementPattern(type, matchOperator, utilStr);
    } else {
        throw std::runtime_error("niepoprawny rodzaj wartosci w deserialziacji elementu");
    }
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
        this->valueToCompare = "";//in order to not throw exception while printing
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
    std::string serialized;
    for (auto &pattern : this->elementPatterns) {
        serialized += pattern.serialize();
    }

    if (serialized.size() > MAX_SIZE_IN_BYTES) {//TODO: zostawiamy to?
        throw std::runtime_error("za duzo rozmiar krotki w bajtach");
    }
    char *bytes = new char[serialized.size()];
    strcpy(bytes, serialized.c_str());
    return bytes;
}

TuplePattern TuplePattern::deserialize(char *serialized) {
    std::string str(serialized);
    delete[] serialized;

    std::vector<TupleElementPattern> elementPatterns;
    while (!str.empty()) {
        TupleElementPattern t2 = TupleElementPattern::deserialize(str);
        elementPatterns.emplace_back(t2);
    }
    return TuplePattern(std::move(elementPatterns));
}

TuplePattern::TuplePattern(std::string patternString) {
    while (!patternString.empty()) {
        std::string elementPatternStr = SerializationUtils::getNextElementAndErase(patternString, ',');
        while (elementPatternStr[0] == ' ') {//get rid of spaces after coma
            elementPatternStr.erase(0, 1);
        }
        this->elementPatterns.emplace_back(TupleElementPattern(elementPatternStr));
    }
}
