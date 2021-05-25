cmake_minimum_required(VERSION 3.17)
project(uxp1a-linda)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS unit_test_framework  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
FILE(GLOB_RECURSE LINDA_SOURCES src/*/*.cpp)
ADD_LIBRARY(linda_objects OBJECT ${LINDA_SOURCES})
add_executable(uxp1a-linda src/main.cpp src/server/WaitingProcess.cpp src/server/MasterProcess.cpp  src/client/linda.cpp src/tuple/Tuple.cpp src/util/SerializationUtils.cpp src/tuple/TuplePattern.cpp)
target_link_libraries(uxp1a-linda ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)