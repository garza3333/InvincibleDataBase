cmake_minimum_required(VERSION 3.13)
project(MyDataBase)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyDataBase main.cpp Structures/AVLTree.cpp Structures/AVLTree.h Structures/Node.cpp Structures/Node.h Objects/Image.cpp Objects/Image.h Objects/JManager.cpp Objects/JManager.h Structures2/Node.cpp Structures2/Node.h Structures2/LinkedList.cpp Structures2/LinkedList.h Objects/DataBase.cpp Objects/DataBase.h)

