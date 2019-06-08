//
// Created by Daniel on 26/05/2019.
//

#ifndef MYDATABASE_NODEH_H
#define MYDATABASE_NODE_H



template <class T>
class NodeHuff {

private:
    NodeHuff<T>* next;
    T value;

public:

    /**
     * Builder of node
     */
    NodeHuff(){
        this->value = 0;
        this->next = 0;
    }
    /**
     * Second builder of node
     * @param v
     */
    NodeHuff(T v){
        this->value = v;
        this->next = 0;
    }
    /**
     * other Builder of node , this include a pointer to next
     * @param v
     * @param n
     */
    NodeHuff(T v , NodeHuff<T>* n ){
        this->value = v;
        this->next = n;
    }
    /**
     *
     * @return the next node
     */
    NodeHuff<T>* getNext(){
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
    void setNext(NodeHuff<T>* n){
        this->next = n;
    }
    /**
     * destroy the pointer of the node
     */
    virtual ~NodeHuff(){
        delete next;
    }

};


#endif //MYDATABASE_NODEH_H
