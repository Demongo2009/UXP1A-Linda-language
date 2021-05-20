//
// Created by konrad on 5/1/21.
//
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "../../include/SerializationUtils.h"
#include "../../include/tuple/Tuple.h"

/*
 * 1. https://stackoverflow.com/questions/5609915/best-practice-for-passing-primitive-data-type-in-c-function
 * 2. https://stackoverflow.com/questions/523872/how-do-you-serialize-an-object-in-c
 * 3. https://stackoverflow.com/questions/11415850/c-how-to-serialize-deserialize-objects-without-the-use-of-libraries?rq=1
 * 4. https://stackoverflow.com/questions/1703322/serialize-strings-ints-and-floats-to-character-arrays-for-networking-without-li
 * 5. https://stackoverflow.com/questions/8513202/c-how-to-send-structures-over-socket
 *
 * https://isocpp.org/wiki/faq/serialization#serialize-binary-format
 * */



TupleElement::TupleElement(const variant& val) {
    this->value = val;
    switch (val.index()) {
        case INT:
            this->valueType = INT;
            break;
        case FLOAT:
            this->valueType = FLOAT;
            break;
        case STRING:
            this->valueType = STRING;
            break;
        default:
            throw std::runtime_error("niepoprawny rodzaj wartosci");
    }
}

std::string TupleElement::serialize() {
    std::stringstream buffer;
    ElemType type = this->valueType;
    buffer << type << Separator;
    if (type == INT)
        buffer << std::get<int>(this->value);
    else if (type == FLOAT)
        buffer << std::get<float>(this->value);
    else if (type == STRING)
        buffer << std::get<std::string>(this->value);
    else
        throw std::runtime_error("niepoprawny rodzaj wartosci w serialziacji elementu");
    buffer << Separator;
    return buffer.str();
}

TupleElement TupleElement::deserialize(std::string &content) {
    std::string utilStr = SerializationUtils::getNextElementAndErase(content);
    auto type = (ElemType) std::stoi(utilStr);

    utilStr = SerializationUtils::getNextElementAndErase(content);
    if (type == INT) {
        int value = std::stoi(utilStr);
        return TupleElement(value);
    } else if (type == FLOAT) {
        float value = std::stof(utilStr);
        return TupleElement(value);
    } else if (type == STRING) {
        return TupleElement(utilStr);
    } else {
        throw std::runtime_error("niepoprawny rodzaj wartosci w deserialziacji elementu");
    }
}

char *Tuple::serialize() {
    std::string serialized;
    for (auto & element : this->elements) {
        serialized += element.serialize();
    }

    if (serialized.size() > MAX_SIZE_IN_BYTES) {//TODO: zostawiamy to?
        throw std::runtime_error("za duzo rozmiar krotki w bajtach");
    }
    char *bytes = new char[serialized.size()];
    strcpy(bytes, serialized.c_str());
    return bytes;
}

Tuple Tuple::deserialize(char *serialized) {
    std::string str(serialized);
    delete[] serialized;

    std::vector<variant> valuesVector;
    while (!str.empty()) {
        TupleElement t2 = TupleElement::deserialize(str);
        valuesVector.emplace_back(t2.getValue());
    }
    return Tuple(valuesVector);
}

Tuple::Tuple(std::vector<variant> vector) {
    int size = vector.size();
//w zasadzie to jak tak serializujemy to niepotrzebny jest TupleElement, ale zostawmy to więcej kodu będzie
    for (int i = 0; i < size; ++i) {
        this->elements.emplace_back(TupleElement(vector[i]));
    }
}
