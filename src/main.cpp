#include <iostream>
#include "tuple/Tuple.h"

int main() {
//    TupleElement t = TupleElement(257);
//    TupleElement t = TupleElement(12.1f);
    TupleElement t = TupleElement("napis");


    char* serialized = t.serialize();
    TupleElement::deserialize(serialized);

//    t.serialize();
    return 0;
}
