cmake_minimum_required(VERSION 3.14.0)
project(Search-Engine VERSION 0.1.0)


set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories( include ${INCLUDE_DIR})

add_library( SRC 
            ${SRC_DIR}/Map.cpp
            ${SRC_DIR}/Maxheap.cpp
            ${SRC_DIR}/Readinput.cpp
            ${SRC_DIR}/Scorelist.cpp
            ${SRC_DIR}/Search.cpp
            ${SRC_DIR}/Trienode.cpp
            ${SRC_DIR}/Listnode.cpp)

set(Searchengine.cpp {CMAKE_DEFAULT_PROJECT_FILE})

add_executable(Search-Engine Searchengine.cpp)

target_link_libraries( Search-Engine SRC)
