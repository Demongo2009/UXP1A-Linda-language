#include "tuple/Tuple.h"
#include <iostream>

int main() {

    Tuple tuple = Tuple({-11, 0.95f, "naaaapis", 1, 1, 1});
    char *serializedTuple = tuple.serialize();
    Tuple tuple2 = Tuple::deserialize(serializedTuple);
    tuple2.print();

    return 0;
}
