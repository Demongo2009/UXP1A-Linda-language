#include <iostream>
#include "tuple/Tuple.h"

int main() {

    Tuple tuple = Tuple({-11, 0.95f, "naaaapis"});
    char* serializedTuple = tuple.serialize();
    Tuple tuple2 = Tuple::deserialize(serializedTuple);
    tuple2.print();

    return 0;
}
