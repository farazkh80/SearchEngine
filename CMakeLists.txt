set(CMAKE_CXX_COMPILER g++)
cmake_minimum_required(VERSION 3.14.0)
project(SearchEngine VERSION 0.1.0)


set(CMAKE_C_COMPILER gcc)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(SYS_DIR ${PROJECT_SOURCE_DIR}/sys)

include_directories( include ${INCLUDE_DIR})
include_directories( sys ${SYS_DIR})

add_library( SRC 
            Map.cpp
            Maxheap.cpp
            Readinput.cpp
            Scorelist.cpp
            Search.cpp
            Trienode.cpp
            Listnode.cpp)

set(Searchengine.cpp {CMAKE_DEFAULT_PROJECT_FILE})

add_executable(SearchEngine Searchengine.cpp)

target_link_libraries( SearchEngine SRC)
