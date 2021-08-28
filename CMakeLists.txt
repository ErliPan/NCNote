cmake_minimum_required(VERSION 3.20)
project(QTNote)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_subdirectory(test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(QTNote main.cpp TextNote.h Collections.h ViewInterface.h NoteInterface.h CollectionInterface.h QTView.h)

target_link_libraries(QTNote Qt5::Core)
target_link_libraries(QTNote Qt5::Widgets)