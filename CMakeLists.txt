cmake_minimum_required(VERSION 3.8)
project(trie_31)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        catch.hpp
        trie.cpp
        trie.hpp
        tests-main.cpp
        trie-tests.cpp)
add_executable(trie_31 ${SOURCE_FILES})