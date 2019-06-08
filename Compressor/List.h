//
// Created by garza on 08/06/19.
//

#ifndef MYDATABASE_LIST_H
#define MYDATABASE_LIST_H


#include "NodeH.h"
#include <iostream>
using namespace std;
template <class T>
class List
{
    private:
        NodeH<T>*head;
        int* length;
        List<T>* next;
    public:
        /**
         * Constructor de la clase List.
         */
        List()
        {
            this->head= nullptr;
            this->length=new int(0);
            this->next= nullptr;
        }
        /**
         * Metodo para añadir un valor a la lista.
         * @param v Valor a añadir.
         */
        void add(T v)
        {
            NodeH<T>* n= new NodeH<T>(v,++*this->length);
            if(this->head== nullptr)
            {
                this->head=n;
            }
            else
            {
                NodeH<T>* temp= this->head;
                while(temp->getNext()!= nullptr)
                {
                    temp=temp->getNext();
                }
                temp->setNext(n);
            }
        }
        /**
         * Metodo para eliminar un valr de la lista.
         * @param o Identificador del nodo donde esta almacenado el valor.
         */
        void del(int o)
        {
            NodeH<T>* temp=this->head;
            if(temp->getOrder()==o)
            {
                this->head=temp->getNext();
                temp->purge();
                delete(temp);
            }
            else
            {
                while (temp->getNext()->getOrder() != o)
                {
                    temp = temp->getNext();
                }
                NodeH<T> *temp2 = temp->getNext();
                temp->setNext(temp2->getNext());
                temp2->purge();
                temp= nullptr;
                delete(temp);
                delete (temp2);
            }
            *this->length=*this->length-1;

        }
        /**
         * Metodo para obtener la lista qu ele sigue a la lista actual.
         * @return Lista siguiente.
         */
        List<T>* getNext()
        {
            return this->next;
        }
        /**
         * Metodo para obtener el tamaño de la lista.
         * @return Tamaño de la lista.
         */
        int getLength()
        {
            return *this->length;
        }
        /**
         * Metodo para establecer la lista que le sigue a la lista actual.
         * @param l Lista siguiente.
         */
        void setNext(List<T>* l)
        {
            this->next=l;
        }
        /**
         * Metodo para obtener la cabeza de la lista.
         * @return Nodo cabeza de la lista.
         */
        NodeH<T>* getHead()
        {
            return this->head;
        }
        /**
         * Metodo para eliminar todos los elementos de la lista.
         */
        void purge()
        {
            int l=this->length;
            for(int i=1;i<=l;i++)
            {
                del(1);
            }
        }
        void setHead(NodeH<T>* h)
        {
            this->head=h;
        }
        void arrange()
        {
            NodeH<T>* temp2= this->head;
            int newOrd=1;
            while(temp2!= nullptr)
            {
                temp2->setOrder(newOrd);
                temp2=temp2->getNext();
                newOrd++;
            }
            temp2= nullptr;
            delete(temp2);
        }
        void delFirst()
        {
            NodeH<T>* temp= this->head;
            this->head=temp->getNext();
            temp->purge();
            delete(temp);
            *this->length=*this->length-1;
            arrange();
        }
};


#endif //MYDATABASE_LIST_H
