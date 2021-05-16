//
// Created by konrad on 5/1/21.
//

#ifndef UXP1A_LINDA_TUPLE_H
#define UXP1A_LINDA_TUPLE_H

#include <variant>
#include <string>

static const int MAX_NO_OF_ELEMENTS = 5;
static const int MAX_SIZE_IN_BYTES = 512;

enum ElemType{INT, FLOAT, STRING};//TODO: te int=1 to na chwile dopoki nie ogarne jak zrobic zeby dorze zapisywalo wszystko jako bajty
typedef std::variant<int, float, std::string> variant;

class TupleElement{
public:
    explicit TupleElement(variant);

    variant getValue();
    ElemType getType();
    size_t getSize();
    std::string serialize();

    static TupleElement deserialize(const char*);

private:
    variant value;
    size_t valueSize; //needed because of strings, since int and floats are always 4bytes
    ElemType valueType;
};

class Tuple {
public:
    Tuple(int noOfElements, ...);

    TupleElement getElement(int index);
    variant getElementsValue(int index);
    ElemType getElementsType(int index);

    char* serialize();
    static Tuple deserialize(char*);

private:
    const int noOfElements;
    TupleElement elements[MAX_NO_OF_ELEMENTS];
};




#endif //UXP1A_LINDA_TUPLE_H
