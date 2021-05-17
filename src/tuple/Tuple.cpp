//
// Created by konrad on 5/1/21.
//
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cstdarg>

#include "Tuple.h"

/*
 * 1. https://stackoverflow.com/questions/5609915/best-practice-for-passing-primitive-data-type-in-c-function
 * 2. https://stackoverflow.com/questions/523872/how-do-you-serialize-an-object-in-c
 * 3. https://stackoverflow.com/questions/11415850/c-how-to-serialize-deserialize-objects-without-the-use-of-libraries?rq=1
 * 4. https://stackoverflow.com/questions/1703322/serialize-strings-ints-and-floats-to-character-arrays-for-networking-without-li
 * 5. https://stackoverflow.com/questions/8513202/c-how-to-send-structures-over-socket
 *
 * https://isocpp.org/wiki/faq/serialization#serialize-binary-format
 * */

const char separator = ';';

TupleElement::TupleElement(variant val){
    this->value = val;
    switch(val.index()){
        case INT:
            this->valueType = INT;
            this->valueSize = sizeof(int);
            break;
        case FLOAT:
            this->valueType = FLOAT;
            this->valueSize = sizeof(float);
            break;
        case STRING:
            this->valueType = STRING;
            this->valueSize = std::get<std::string>(val).size();
            break;
        default:
            throw("TupleElement constructor");
    }
}

std::string TupleElement::serialize(){
//    std::stringstream buffer;
//    buffer.write(reinterpret_cast<char*>(&this->valueType), sizeof(this->valueType));
//    buffer.write(reinterpret_cast<char*>(&this->valueSize), sizeof(this->valueSize));
//    buffer.write(reinterpret_cast<char*>(&this->value), valueSize);

    std::stringstream buffer;
    ElemType type = this->valueType;
    buffer << type << separator;
//    buffer << this->valueSize << separator; // TODO: rozmiar niepotrzebny jak inty i floaty, to potem mozemy optymalizowac
    if( type == INT)
        buffer << std::get<int>(this->value);
    else if( type == FLOAT)
        buffer << std::get<float>(this->value);
    else if( type == STRING)
        buffer << std::get<std::string>(this->value);
    else
        throw;
    buffer << separator;
    return buffer.str();


//    size_t serialized_size = sizeof(this->valueSize) + sizeof(this->valueType) + valueSize; //TODO: tu te ograniczenie na 512bajtów
//    char* bytes = new char[serialized_size];
//    strcpy(bytes, buffer.str().c_str());
//    return bytes;
}

TupleElement TupleElement::deserialize(std::string& content) {
//    std::stringstream buffer(serialized);
//    buffer.read(reinterpret_cast<char*>(&type), sizeof(ElemType));
//    buffer.read(reinterpret_cast<char*>(&size), sizeof(size_t));
//    buffer.read(reinterpret_cast<char*>(&value1), size);

    std::string utilStr = content.substr(0, content.find(separator));
    ElemType type = (ElemType)std::stoi(utilStr);
    content.erase(0, content.find(separator) +1);

    utilStr = content.substr(0, content.find(separator));
    content.erase(0, content.find(separator) +1);
    if(type == INT){
        int value = std::stoi(utilStr);
        return TupleElement(value);
    }else if(type == FLOAT){
        float value = std::stof(utilStr);
        return TupleElement(value);
    }else if(type == STRING) {
        return TupleElement(utilStr);
    }else{
        throw;
    }
}

char * Tuple::serialize() {
    char* tuplesBytes = nullptr;
    std::string serialized = std::to_string(this->noOfElements) + separator;
    std::string serializedTuples;
    for(int i = 0; i<this->noOfElements; ++i) {
        serializedTuples += this->elements[i].serialize();
    }


    serialized += serializedTuples;
    if( serialized.size() > MAX_SIZE_IN_BYTES){ //nie wiem essa
        throw;
    }
    char* bytes = new char[serialized.size()];
    strcpy(bytes, serialized.c_str());
    return bytes;
}

Tuple Tuple::deserialize(char* serialized) {
    std::string str(serialized);
    delete[] serialized;

    std::string utilStr = str.substr(0, str.find(separator));
    int noOfElements = std::stoi(utilStr);
    str.erase(0, str.find(separator) +1);

    std::vector<variant> valuesVector;
    while(str != ""){
        TupleElement t2 = TupleElement::deserialize(str);
        valuesVector.emplace_back(t2.getValue());
    }
    return Tuple(valuesVector);
}

Tuple::Tuple(std::vector<variant> vector){
    int size = vector.size();
    if(size <= 0 || size > MAX_NO_OF_ELEMENTS){
        throw;//w zasadzie to nie ma sensu dawanie tego statycznego ograniczenia
    }

    for(int i = 0; i<size; ++i){
        this->elements.emplace_back(TupleElement(vector[i]));
    }
    this->noOfElements = size;

}
