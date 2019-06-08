cmake_minimum_required(VERSION 3.13)
project(MyDataBase)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyDataBase main.cpp Objects/Image.cpp Objects/Image.h Objects/JManager.cpp Objects/JManager.h Structures/NodeHuff.cpp Structures/Node.h Structures/LinkedList.cpp Structures/LinkedList.h Objects/DataBase.cpp Objects/DataBase.h  Tests/test.cpp main.cpp  Compressor/Compressor.cpp Compressor/Compressor.h Compressor/Huffman_Node.cpp Compressor/Huffman_Node.h Compressor/Huffman_Tree.cpp Compressor/Huffman_Tree.h Compressor/List.h Compressor/NodeH.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
target_link_libraries(MyDataBase gtest gtest_main)
