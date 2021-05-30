#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TupleTests
#include "../include/tuple/Tuple.h"
#include "../include/tuple/TuplePattern.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tuple_tests)

    BOOST_AUTO_TEST_CASE(case1)
    {
        Tuple tuple = Tuple({"aaa"});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);
        tuple2.print();


        BOOST_TEST(tuple.getElementsType(0) == tuple2.getElementsType(0));
        BOOST_TEST(tuple.getNumberOfElements() == tuple2.getNumberOfElements());
    }

    BOOST_AUTO_TEST_CASE(case2)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:>aab");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);
        tuplePattern2.print();

        BOOST_TEST(!tuplePattern2.checkIfMatch(tuple));
    }

BOOST_AUTO_TEST_SUITE_END();

