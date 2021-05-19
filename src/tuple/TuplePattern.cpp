//
// Created by Konrad Kulesza on 19.05.2021.
//

#include "../../include/tuple/TuplePattern.h"
bool TupleElementPattern::checkIfMatch(TupleElement) {
    return false;
}
char *TupleElementPattern::serialize() {
    return nullptr;
}
TupleElementPattern TupleElementPattern::deserialize(char *) {
    return TupleElementPattern();
}



bool TuplePattern::checkIfMatch(Tuple) {
    return false;
}
char *TuplePattern::serialize() {
    return nullptr;
}
TuplePattern TuplePattern::deserialize(char *) {
    return TuplePattern();
}
