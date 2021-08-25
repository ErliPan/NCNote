cmake_minimum_required(VERSION 3.20)
project(NCNote)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

set(SRC_FILE Note.cpp Note.h Collection.cpp Collection.h ViewInterface.h NoteInterface.h CollectionInterface.h NCView.cpp NCView.h)
add_executable(NCNote main.cpp)
add_library(Note ${SRC_FILE})
target_link_libraries(NCNote Note)
