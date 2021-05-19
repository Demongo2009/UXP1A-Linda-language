//
// Created by konrad on 5/1/21.
//

#ifndef UXP1A_LINDA_TUPLE_H
#define UXP1A_LINDA_TUPLE_H

#include "../consts.h"
#include <iostream>
#include <string>
#include <vector>


class TupleElement {
public:
    explicit TupleElement(const variant&);

    [[nodiscard]] variant getValue() const { return value; };
    [[nodiscard]] ElemType getType() const { return valueType; };

    std::string serialize();
    static TupleElement deserialize(std::string &);

    //for debug
    void print() {
        if (valueType == INT)
            std::cout << std::get<int>(value);
        else if (valueType == FLOAT)
            std::cout << std::get<float>(value);
        else if (valueType == STRING)
            std::cout << std::get<std::string>(value);
    }

private:
    variant value;
    ElemType valueType;
};

class Tuple {
public:
    explicit Tuple(std::vector<variant>);

    //TODO: jakies sprawdzanie indexu- ale to ewentualnie potem
    [[nodiscard]] TupleElement getElement(int index) const { return elements[index]; };
    [[nodiscard]] variant getElementsValue(int index) const { return elements[index].getValue(); };
    [[nodiscard]] ElemType getElementsType(int index) const { return elements[index].getType(); };
    [[nodiscard]] int getNumberOfElements() const { return elements.size(); };

    char *serialize();
    static Tuple deserialize(char *);

    //for debug
    void print() {
        int noOfElements = elements.size();
        std::cout << "krotka " << noOfElements << ". elementowa:\n";
        for (int i = 0; i < noOfElements; ++i) {
            std::cout << "\t" << i << ": ";
            elements[i].print();
            std::cout << std::endl;
        }
    }

private:
    std::vector<TupleElement> elements;
};

#endif//UXP1A_LINDA_TUPLE_H
