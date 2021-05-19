cmake_minimum_required(VERSION 3.17)
project(uxp1a-linda)

set(CMAKE_CXX_STANDARD 17)

add_executable(uxp1a-linda src/main.cpp src/tuple/Tuple.cpp src/serialization_utils.h src/serializtion_utils.cpp src/consts.h src/tuple/TuplePattern.cpp src/tuple/TuplePattern.h)