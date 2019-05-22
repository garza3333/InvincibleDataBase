//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_NODE_H
#define MYDATABASE_NODE_H
#include <string.h>
#include <string>
#include <iostream>

class Node {

private:
    std::string name , author ;
    int size , year;

    Node * right;
    Node * left;
    int height;


};


#endif //MYDATABASE_NODE_H
