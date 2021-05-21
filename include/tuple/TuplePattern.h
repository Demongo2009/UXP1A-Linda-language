//
// Created by Konrad Kulesza on 19.05.2021.
//

#ifndef UXP1A_LINDA_TUPLE_PATTERN_H
#define UXP1A_LINDA_TUPLE_PATTERN_H

#include "../SerializationUtils.h"
#include "Tuple.h"

class TupleElementPattern {
public:
    TupleElementPattern(std::string);

    bool checkIfMatch(TupleElement);
    std::string serialize();
    static TupleElementPattern deserialize(std::string &);


    //for debug
    void print() {
        SerializationUtils::printType(valueType);
        std::cout << ":";
        SerializationUtils::printOperator(matchOperatorType);
        SerializationUtils::printVariant(valueToCompare);
    }

private:
    ValueType valueType;
    MatchOperatorType matchOperatorType;
    variant valueToCompare;

    TupleElementPattern(ValueType ty, MatchOperatorType op, variant val)
        : valueType(ty),
          matchOperatorType(op),
          valueToCompare(val){};
};

class TuplePattern {
public:
    TuplePattern(std::string);

    bool checkIfMatch(Tuple);
    char *serialize();
    static TuplePattern deserialize(char *);
    [[nodiscard]] int getNumberOfElements() const { return elementPatterns.size(); };

    void print() {
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
    TuplePattern(std::vector<TupleElementPattern> vec) : elementPatterns(std::move(vec)){};//for deserialization
};


#endif//UXP1A_LINDA_TUPLE_PATTERN_H
