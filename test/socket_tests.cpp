//
// Created by bartlomiej on 24.05.2021.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SocketTests
#include <boost/test/unit_test.hpp>
#include "../include/client/linda.h"
#include <bits/stdc++.h>
#include <chrono>

BOOST_AUTO_TEST_SUITE(socket_tests)

    BOOST_AUTO_TEST_CASE(case1)
    {
        Tuple tuple = Tuple({"aaa"});
        auto start = std::chrono::high_resolution_clock::now();

        // unsync the I/O of C and C++.
        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 100; ++i)
            linda_output(tuple);
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
             << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
//        BOOST_TEST(analyzed == expected);
    }

    BOOST_AUTO_TEST_CASE(Error_1)
    {
//        BOOST_CHECK_THROW (s.check();, std::runtime_error);
    }

BOOST_AUTO_TEST_SUITE_END();