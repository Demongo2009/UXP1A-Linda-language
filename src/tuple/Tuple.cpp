//
// Created by konrad on 5/1/21.
//


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sstream>

#include "Tuple.h"



TupleElement::TupleElement(variant val){
    this->value = val;
    switch(val.index()){
        case INT:
            this->valueType = INT;
            this->valueSize = sizeof(int); // tu mozna dac jakis int32
            break;
        case FLOAT:
            this->valueType = FLOAT;
            this->valueSize = sizeof(float); // tu tez jakis float32?
            break;
        case STRING:
            this->valueType = STRING;
            this->valueSize = std::get<std::string>(val).size();
            break;
        default:
            throw("TupleElement constructor");
    }
}

variant TupleElement::getValue(){
    return this->value;
}

ElemType TupleElement::getType(){
    return this->valueType;
}

size_t TupleElement::getSize(){
    return this->valueSize;
}

std::string TupleElement::serialize(){
    std::stringstream buffer;

//    buffer.write(reinterpret_cast<char*>(&this->valueType), sizeof(this->valueType));
//    buffer.write(reinterpret_cast<char*>(&this->valueSize), sizeof(this->valueSize));
//    buffer.write(reinterpret_cast<char*>(&this->value), valueSize);
    buffer <<std::to_string( this->valueType)<<";" << std::to_string(this->valueSize) <<";"<< std::to_string(1);
    return buffer.str();

//    size_t serialized_size = sizeof(this->valueSize) + sizeof(this->valueType) + valueSize;
//    std::cout<<sizeof(this->valueSize)<<std::endl;
//    char* bytes = new char[serialized_size]; //pamiętać o delete
//    buffer.get(bytes, serialized_size);
//    std::cout<<bytes<<std::endl;
//    return bytes;


//    std::stringstream buffer2(bytes);
    ElemType type;
    size_t size;

//    int value1;
    std::string value1;
//    float value1;

    buffer.read(reinterpret_cast<char*>(&type), sizeof(ElemType));
    buffer.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    buffer.read(reinterpret_cast<char*>(&value1), size);
    std::cout<<"typ: "<<type<<"\nrozmiar: "<<size<<"\nwartosc: "<<value1<<std::endl;
    std::cout<<"dupa"<<std::endl;
}

TupleElement TupleElement::deserialize(const char *serialized) {
    std::string type;
    std::string size;

    std::string value1;
//    std::string value1;
//    float value1;


    std::stringstream buffer(serialized);
//    buffer.read(reinterpret_cast<char*>(&type), sizeof(ElemType));
//    buffer.read(reinterpret_cast<char*>(&size), sizeof(size_t));
//    buffer.read(reinterpret_cast<char*>(&value1), size);
//    std::string typeStr;
    buffer >> value1;
    buffer >>size;
    buffer >> type;


//    type = *(ElemType*)typeStr;
    std::cout<<"typ: "<<type<<"\nrozmiar: "<<size<<"\nwartosc: "<<value1<<std::endl;

}