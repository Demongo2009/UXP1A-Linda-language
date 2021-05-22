#include "../include/tuple/Tuple.h"
#include "../include/tuple/TuplePattern.h"
#include <iostream>

int main() {

    Tuple tuple = Tuple({"aaa"});
    char *serializedTuple = tuple.serialize();
    Tuple tuple2 = Tuple::deserialize(serializedTuple);
    tuple2.print();

    TuplePattern tuplePattern = TuplePattern("string:>aab");
    char *serializedTuplePattern = tuplePattern.serialize();
    TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);
    tuplePattern2.print();

    if(tuplePattern.checkIfMatch(tuple)){
        std::cout<<"PRAWDA";
    }else{
        std::cout<<"FALSE";
    }


    return 0;
}
