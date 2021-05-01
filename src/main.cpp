#include <iostream>
#include "tuple/Tuple.h"

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    TupleElement t = TupleElement(12);
            // TupleElement("japierdolekurwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    char* serialized = t.serialize();
//    puts(serialized);
    TupleElement::deserialize(serialized);
//    int num = 10;
//    char* arr;
//    memcpy(arr, &num, sizeof(num));
//    int num2 = *(int*)arr;
//    std::cout<<num2<<std::endl;
    return 0;
}
