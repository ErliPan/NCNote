cmake_minimum_required(VERSION 3.20)
project(NCNote)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_executable(NCNote main.cpp TextNote.h Collections.h ViewInterface.h NoteInterface.h CollectionInterface.h QTView.h QTView.cpp)
