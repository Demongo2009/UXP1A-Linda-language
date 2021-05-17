//
// Created by konrad on 5/1/21.
//

#ifndef UXP1A_LINDA_TUPLE_H
#define UXP1A_LINDA_TUPLE_H

#include <string>
#include <variant>
#include <vector>

static const int MAX_NO_OF_ELEMENTS = 5;
static const int MAX_SIZE_IN_BYTES = 512;

enum ElemType { INT,
                FLOAT,
                STRING };
typedef std::variant<int, float, std::string> variant;

class TupleElement {
public:
    explicit TupleElement(variant);

    [[nodiscard]] variant getValue() const { return value; };
    [[nodiscard]] ElemType getType() const { return valueType; };
    [[nodiscard]] size_t getSize() const { return valueSize; };

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
    size_t valueSize;
    ElemType valueType;
};

class Tuple {
public:
    explicit Tuple(std::vector<variant>);

    [[nodiscard]] TupleElement getElement(int index) const { return elements[index]; };//TODO: jakies sprawdzanie indexu- ale to ewentualnie potem
    [[nodiscard]] variant getElementsValue(int index) const { return elements[index].getValue(); };
    [[nodiscard]] ElemType getElementsType(int index) const { return elements[index].getType(); };

    char *serialize();
    static Tuple deserialize(char *);

    //for debug
    void print() {
        std::cout << "krotka " << noOfElements << ". elementowa:\n";
        for (int i = 0; i < noOfElements; ++i) {
            std::cout << "\t" << i << ": ";
            elements[i].print();
            std::cout << std::endl;
        }
    }

private:
    int noOfElements;
    std::vector<TupleElement> elements;
};

#endif//UXP1A_LINDA_TUPLE_H
