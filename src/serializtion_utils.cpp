//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "serialization_utils.h"
#include "consts.h"


std::string getNextElementAndErase(std::string& str){
    auto idx = str.find(separator);
    std::string contentStr = str.substr(0, idx);
    str.erase(0, idx + 1);
    return std::move(contentStr);
}