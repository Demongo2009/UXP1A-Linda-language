//
// Created by konrad on 5/1/21.
//


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "Tuple.h"



TupleElement::TupleElement(variant val){
    this->value = val;
    switch(val.index()+1){
        case INT:
            this->valueType = INT;
            this->valueSize = 4;//TODO: to do zmiany
            break;
        case FLOAT:
            this->valueType = FLOAT;
            this->valueSize = 4;//TODO: to do zmiany
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

int TupleElement::getSize(){
    return this->valueSize;
}

char* TupleElement::serialize(){
    char serializedType[sizeof(ElemType)];
    char serializedSize[sizeof(int)];
    char serializedValue[this->valueSize+1];

//TODO: tutaj trzeba zmienic bo kopiuje tylko ten jeden zajęty bajt, a chcemy zeby brało 4 chyba
    memcpy(serializedType, &(this->valueType), sizeof(serializedType));
    memcpy(serializedSize, &(this->valueSize), sizeof(serializedSize));


    ElemType type = *(ElemType*)serializedType;
    int size = *(int*)serializedSize;
    std::cout<<"typ po odczytaniu: "<<type<<std::endl;
    std::cout<<"rozmiar po odczytaniu: "<<size<<std::endl;


    if(valueType == INT){
        memcpy(serializedValue, &std::get<int>(this->value), valueSize);
    }else if(type == FLOAT) {
//        memcpy(serializedValue, &std::get<float>(this->value), valueSize);
        snprintf(serializedValue, sizeof(serializedValue), "%f", std::get<float>(this->value));
    }else if(type == STRING){
        memcpy(serializedValue, std::get<std::string>(this->value).c_str(), valueSize);
    }
    size_t resultSize = sizeof(serializedType) + sizeof(serializedValue) + sizeof(serializedSize);
//    char* result = new char[resultSize];
    char* result = new char();
//TODO: trzeba jakos zrobić żeby zawsze zapisywało 4 bajty ORAZ żeby potem dobrze je odczytywało.
//TODO:To musi być kurwa proste ale mi nie wychodzi
    strncat(result, serializedType, sizeof(ElemType));
    strncat(result+4, serializedSize, sizeof(int));
    strncat(result+8, serializedValue, valueSize);
//    strcpy(result, serializedType);
//    strcat(result, serializedSize);
//    strcat(result, serializedValue);

    puts(result);
    puts(result+4);
    puts(result+8);

    return result;
}

TupleElement TupleElement::deserialize(char *serialized) {
    std::cout<<"---------------------------------"<<std::endl;
    int length = strlen(serialized);

    char typeChunk[sizeof(ElemType)];
    char sizeChunk[sizeof(int)];

    memcpy(typeChunk, serialized, 4);
    memcpy(sizeChunk, serialized+4, 4);

    //TODO: nie wiem co sie dzieje, ale jak string jest dłuższy niż 256 to mimo ze czytam jeden byte to i tak pokazuje dobrą

    ElemType type = *(ElemType*)typeChunk;
    int size = *(int*)sizeChunk;
    std::cout<<"otrzymany type: "<<type<<std::endl;
    std::cout<<"otrzymany size: "<<size<<std::endl;

    char valueChunk[size];
//    int offset = ceil(size/256.0);//TODO: wiem ze tak nie moze byc ale XDD dziala
//    std::cout<<"offset: "<<offset<<std::endl;
    memcpy(valueChunk, serialized+8, size);
    if(type == INT){
        int value = *(int*)valueChunk;
        std::cout<<"otrzymano int: "<<value<<std::endl;
    }else if(type == FLOAT){
        float value = *(float*)valueChunk;
        std::cout<<"otrzymano float: "<<value<<std::endl;
    }else if(type == STRING){
        std::string value(valueChunk);
        std::cout<<"otrzymano string: "<<value<<std::endl;
    }

    delete [] serialized;

}