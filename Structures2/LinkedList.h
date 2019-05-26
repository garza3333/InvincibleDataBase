//
// Created by Daniel on 26/05/2019.
//

#ifndef MYDATABASE_LINKEDLIST_H
#define MYDATABASE_LINKEDLIST_H

#include "iostream"
#include "Node.h"


using  namespace std;
template<class T>
class LinkedList {

private:
    int size;
    Node<T>* head;
    Node<T> * curr;
    Node<T> * temp;
public:
    /**
     * Builder of the class
     */
    LinkedList(){
         this->size = 0;
         this->head = NULL;
         this->curr = NULL;
         this->temp = NULL;
    }

    /**
     * Veriify if head its equal to null
     * @return true if is null , false if not
     */
    bool isEmpty(){
        return this->head==0;
    }
    /**
     * Assign the head of the list
     * @param newNode
     */
    void setHEAD(Node<T> * newNode){
        head = newNode;
    }
    Node<T> * getCurr(){
        return this->curr;
    }
    Node<T> * getTemp(){
        return this->temp;
    }
    void setCurr(Node<T> * node){
        this->curr = node;
    }
    void setTemp(Node<T> * node){
        this->temp = node;
    }
    /**
     * Substract one to the size
     */
    void substractSize(){ this->size--; }

    /**
     *
     * @return head node of list
     */
    Node<T>* getHead(){
        return this->head;
    }
    /**
     *
     * @return size of list
     */
    int getSize(){
        return this->size;
    }
    /**
     * Add a value to the end of the list
     * @param v new element
     */
    void add(T v){

        if (isEmpty()) {
            this->head = new Node<T>(v);
        } else {
            this->curr = this->getHead();
            while (curr->getNext() != 0) {
                curr = curr->getNext();
            }
            Node<T> *n = new Node<T>(v);
            curr->setNext(n);
        }
        size++;
    }
    /**
     * Add a element in the begin of the list
     * @param v new element
     */
    void addFirst(T v){
        if(isEmpty()){

            this->head = new Node<T>(v);

        }else{
            Node<T>* temp = this->getHead();
            Node<T>* n = new Node<T>(v);
            n->setNext(this->getHead());
            this->head = n;
        }size++;
    }
    /**
     * Delete a node for reference
     * @param n node to delete
     */
    bool delNode(T n){
        if(!this->isEmpty()){


            Node<T> * delPtr = NULL;
            temp = head;
            curr = head;
            if(curr->getValue() == n){
                delPtr = head;
                head = head->getNext();
                delPtr->setNext(NULL);
                delete delPtr;
                return true;
            }
            while(curr != NULL && curr->getValue() != n){
                temp = curr;
                curr = curr->getNext();
            }
            if(curr == NULL){
                cout<<"Ese valor no se encontraba en la lista"<<endl;
                delete delPtr;
                return false;

            }else{
                temp->setNext(curr->getNext());
                curr->setNext(NULL);
                delPtr = curr;
                delete delPtr;
                return true;
            }
        }
    }
    /**
     * Verify if an element is in the list
     * @param v value to verify
     * @return true if it exists , false if not
     */
    bool in(T v){
        Node<T>* temp = this->getHead();
        while(temp!=0){
            if(temp->getValue() == v){
                return true;
            }
            temp = temp->getNext();

        }return false;
    }

    /**
     * Print the list in console
     */
    void see(){

        if(!isEmpty()){
            Node<T>* temp = this->getHead();
            cout<<"[";
            while(temp->getNext() != 0){
                cout<<temp->getValue()<<", ";
                temp = temp->getNext();
            }cout<<temp->getValue()<<"]"<<endl;
        }else{
            cout<<"[]"<<endl;
        }
    }



};

#endif //MYDATABASE_LINKEDLIST_H
