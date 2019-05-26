//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_AVLTREE_H
#define MYDATABASE_AVLTREE_H

#include<iostream>
#include "Node.h"
using namespace std;
template <class T>
class AVLTree {

private:
    Node<T> * root;

public:

    AVLTree()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, this->getRoot());
    }

    void remove(int x)
    {
        root = remove(x, this->getRoot());
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }
    Node<T> * getRoot(){
        return this->root;
    }

    void makeEmpty(Node<T> * t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    Node<T> * insert(T x, Node<T> * t)
    {
        if(t == NULL)
        {
            t = new Node<T>(x);
        }
        else if(x < t->getValue())
        {
            t->setLeft(insert(x,t->getLeft()));
            if(height(t->getLeft()) - height(t->getRight()) == 2)
            {
                if(x < t->getLeft()->getValue())
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->getValue())
        {
            t->setRight(insert(x,t->getRight()));
            if(height(t->getRight()) - height(t->getLeft()) == 2)
            {
                if(x > t->getRight()->getValue())
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        t->setHeight(max(height(t->getLeft()),height(t->getRight())) +1);
        return t;
    }

    Node<T> * singleRightRotate(Node<T>* &t)
    {
        Node<T>* u = t->getLeft();
        t->setLeft(u->getRight());
        u->setRight(t);
        t->setHeight(max(height(t->getLeft()), height(t->getRight()))+1);
        u->setHeight(max(height(u->getLeft()), t->getHeight())+1);
        return u;
    }

    Node<T>* singleLeftRotate(Node<T>* &t)
    {
        Node<T>* u = t->getRight();
        t->setRight(u->getLeft());
        u->setLeft(t);
        t->setHeight(max(height(t->getLeft()), height(t->getRight()))+1);
        u->setHeight(max(height(t->getRight()), t->getHeight())+1);
        return u;
    }

    Node<T>* doubleLeftRotate(Node<T>* &t)
    {
        t->setRight(singleRightRotate(t->getRight()));
        return singleLeftRotate(t);
    }

    Node<T>* doubleRightRotate(Node<T>* &t)
    {
        t->setLeft(singleLeftRotate(t->getLeft()));
        return singleRightRotate(t);
    }

    Node<T> * findMin(Node<T> * t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    Node<T> * findMax(Node<T> * t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    Node<T>* remove(int x, Node<T>* t)
    {
        Node<T>* temp;

        // Element not found
        if(t == NULL)
            return NULL;

            // Searching for element
        else if(x < t->getValue())
            t->left = remove(x, t->left);
        else if(x > t->getValue())
            t->right = remove(x, t->right);

            // Element found
            // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
            // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
                // right left case
            else
                return doubleLeftRotate(t);
        }
            // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
                // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(Node<T> * t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(Node<T> * t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->getLeft()) - height(t->getRight());
    }

    void inorder(Node<T> * t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }



};


#endif //MYDATABASE_AVLTREE_H
