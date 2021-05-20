#include "../include/tuple/Tuple.h"
#include "../include/tuple/TuplePattern.h"
#include <iostream>

int main() {

    Tuple tuple = Tuple({-11, 0.95f, "naaaapis", 1, 1, "na", 0.05f});
    char *serializedTuple = tuple.serialize();
    Tuple tuple2 = Tuple::deserialize(serializedTuple);
    tuple2.print();

    TuplePattern pattern = TuplePattern("string:*, integer:==1");
    pattern.print();
    return 0;
}
