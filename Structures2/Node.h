//
// Created by Daniel on 26/05/2019.
//

#ifndef MYDATABASE_NODE_H
#define MYDATABASE_NODE_H



template <class T>
class Node {

private:
    Node<T>* next;
    T value;

public:

    /**
     * Builder of node
     */
    Node(){
        this->value = 0;
        this->next = 0;
    }
    /**
     * Second builder of node
     * @param v
     */
    Node(T v){
        this->value = v;
        this->next = 0;
    }
    /**
     * other Builder of node , this include a pointer to next
     * @param v
     * @param n
     */
    Node(T v , Node<T>* n ){
        this->value = v;
        this->next = n;
    }
    /**
     *
     * @return the next node
     */
    Node<T>* getNext(){
        return this->next;
    }
    /**
     *
     * @return value in this node
     */
    T getValue(){
        return value;
    }
    /**
     * assign a value to the node
     * @param t value to replace
     */
    void setValue(T t){
        this->value = t;
    }
    /**
     * assign the next node of this
     * @param n
     */
    void setNext(Node<T>* n){
        this->next = n;
    }
    /**
     * destroy the pointer of the node
     */
    virtual ~Node(){
        delete next;
    }

};


#endif //MYDATABASE_NODE_H
