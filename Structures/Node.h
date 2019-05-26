//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_NODE_H
#define MYDATABASE_NODE_H
#include <string.h>
#include <string>
#include <iostream>
template <class T>
class Node{

private:
    int height;
    Node<T> * right;
    Node<T> * left;
    T value;
public:
    Node(T val){
        this->right = this->left = NULL;
        this->height = 0;
        this->value = val;
    }
    void setLeft(Node<T> l){
        this->left = l;
    }
    Node<T> * getLeft(){
        return this->left;
    }
    void setRight(Node<T> r){
        this->right = r;
    }
    Node<T> * getRight(){
        return this->right;
    }
    void setHeight(int h){
        this->height = h;
    }
    int getHeight(){
        return this->height;
    }
    void setValue(T v){
        this->value = v;
    }
    T getValue(){
        return this->value;
    }

};




#endif //MYDATABASE_NODE_H
