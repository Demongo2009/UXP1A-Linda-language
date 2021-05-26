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

    BOOST_AUTO_TEST_CASE(case_output)
    {
        Tuple tuple = Tuple({"aaa"});
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i)
            linda_output(tuple);
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
             << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
//        BOOST_TEST(analyzed == expected);
    }

    BOOST_AUTO_TEST_CASE(case_input)
    {
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i) {
            std::cout << " AAA " << std::endl;
            if(std::optional<Tuple> t = linda_input(tuplePattern, 1000)){
                std::cout<<"Input received: ";
                t.value().print();
                std::cout<<std::endl;
            } else{
                std::cout<<"Input received null: ";
                std::cout<<std::endl;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
//        BOOST_TEST(analyzed == expected);
    }

    BOOST_AUTO_TEST_CASE(case_read)
    {
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i) {
            if(std::optional<Tuple> t = linda_read(tuplePattern, 1000)){
                std::cout<<"Read received: ";
                t.value().print();
                std::cout<<std::endl;
            } else{
                std::cout<<"Read received null: ";
                std::cout<<std::endl;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
//        BOOST_TEST(analyzed == expected);
    }

    BOOST_AUTO_TEST_CASE(case_output_read)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();
        std::ios_base::sync_with_stdio(false);

        for( int i = 0; i< 5; ++i)
            linda_output(tuple);

        for( int i = 0; i< 1; ++i) {
            if(std::optional<Tuple> t = linda_read(tuplePattern, 0)){
                std::cout<<"Read received: ";
                t.value().print();
                std::cout<<std::endl;
            } else{
                std::cout<<"Read received null: ";
                std::cout<<std::endl;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(case_output_input)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();
        std::ios_base::sync_with_stdio(false);

        for( int i = 0; i< 1; ++i)
            linda_output(tuple);

        for( int i = 0; i< 1; ++i) {
            if(std::optional<Tuple> t = linda_input(tuplePattern, 100)){
                std::cout<<"Input received: ";
                t.value().print();
                std::cout<<std::endl;
            } else{
                std::cout<<"Input received null: ";
                std::cout<<std::endl;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;

    }

    BOOST_AUTO_TEST_CASE(Error_1)
    {
//        BOOST_CHECK_THROW (s.check();, std::runtime_error);
    }

BOOST_AUTO_TEST_SUITE_END();