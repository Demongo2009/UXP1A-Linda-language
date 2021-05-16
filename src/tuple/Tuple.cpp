//
// Created by konrad on 5/1/21.
//
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cstdarg>

#include "Tuple.h"

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

char* TupleElement::serialize(){
//    std::stringstream buffer;
//    buffer.write(reinterpret_cast<char*>(&this->valueType), sizeof(this->valueType));
//    buffer.write(reinterpret_cast<char*>(&this->valueSize), sizeof(this->valueSize));
//    buffer.write(reinterpret_cast<char*>(&this->value), valueSize);
    char separator = ';';
    std::stringstream buffer;
    ElemType type = this->valueType;
    buffer << type << separator;
    buffer << this->valueSize << separator; // TODO: to niepotrzebne jak inty i floaty
    if( type == INT)
        buffer << std::get<int>(this->value);
    else if( type == FLOAT)
        buffer << std::get<float>(this->value);
    else if( type == STRING)
        buffer << std::get<std::string>(this->value);
    else
        throw;
    buffer << separator;
//    return buffer.str();


    size_t serialized_size = sizeof(this->valueSize) + sizeof(this->valueType) + valueSize; //TODO: tu te ograniczenie na 512bajtów
    char* bytes = new char[serialized_size]; //TODO: delete
    strcpy(bytes, buffer.str().c_str());
    return bytes;
}

TupleElement TupleElement::deserialize(const char *serialized) {
//    std::stringstream buffer(serialized);
//    buffer.read(reinterpret_cast<char*>(&type), sizeof(ElemType));
//    buffer.read(reinterpret_cast<char*>(&size), sizeof(size_t));
//    buffer.read(reinterpret_cast<char*>(&value1), size);

    std::stringstream buffer(serialized);
    std::string content;
    buffer >> content;

    std::cout<<"otrzymana zawartosc: "<<content<<std::endl;
    delete [] serialized;
}

//Tuple::Tuple(int noOfElements, ...) {
//    if(noOfElements < 0 || noOfElements > 5)
//        throw;
//
//    va_list ap;
//    va_start(ap, noOfElements);
//    for(int i=0; i<noOfElements; ++i){
//        variant arg = va_arg(ap, variant); //TODO: chyba nie da się zrobić generycznego konstruktora z wariantem
//        elements[i] = TupleElement(arg);
//    }
//    va_end(ap);
//}
