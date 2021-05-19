//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "../include/consts.h"
#include "../include/serialization_utils.h"


std::string getNextElementAndErase(std::string& str, char separator){
    auto idx = str.find(separator);
    std::string contentStr = str.substr(0, idx);
    str.erase(0, idx + 1);
    return std::move(contentStr);
}