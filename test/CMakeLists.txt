cmake_minimum_required(VERSION 3.20)
project(NCNote_tests)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE ./lib/googletest)

include_directories(${gtest_SOURCE}/include ${gtest_SOURCE})

add_executable(NCNote_tests runTests.cpp)
target_link_libraries(NCNote_tests noteLib gtest gtest_main)
