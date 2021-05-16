//
// Created by konrad on 5/1/21.
//

#ifndef UXP1A_LINDA_TUPLE_H
#define UXP1A_LINDA_TUPLE_H

#include <variant>
#include <string>

static const int MAX_NO_OF_ELEMENTS = 5;
static const int MAX_SIZE_IN_BYTES = 512;

enum ElemType{INT, FLOAT, STRING};
typedef std::variant<int, float, std::string> variant;

class TupleElement{
public:
    explicit TupleElement(variant);

    variant getValue(){return value;};
    ElemType getType(){return valueType;};
    size_t getSize()  {return valueSize;};

    char* serialize();
    static TupleElement deserialize(const char*);

private:
    variant value;
    size_t valueSize;
    ElemType valueType;
};

class Tuple {
public:
    Tuple(int noOfElements, ...);

    TupleElement getElement(int index) {return elements[index];}; //TODO: jakies sprawdzanie indexu- ale to ewentualnie potem
    variant getElementsValue(int index){return elements[index].getValue();};
    ElemType getElementsType(int index){return elements[index].getType();};

    char* serialize();
    static Tuple deserialize(char*);

private:
    const int noOfElements;
    TupleElement elements[MAX_NO_OF_ELEMENTS];
};

#endif //UXP1A_LINDA_TUPLE_H
