//
// Created by garza on 08/06/19.
//

#ifndef MYDATABASE_HUFFMAN_TREE_H
#define MYDATABASE_HUFFMAN_TREE_H


#include "Huffman_Node.h"
class Huffman_Tree
{
private:
    Huffman_Node* Top;
public:
    Huffman_Tree();
    Huffman_Node* getTop();
    void setTop(Huffman_Node* h);

};

#endif //MYDATABASE_HUFFMAN_TREE_H
