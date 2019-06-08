//
// Created by garza on 08/06/19.
//

#ifndef MYDATABASE_NODEH_H
#define MYDATABASE_NODEH_H


template <class T>
class NodeH
{
private:
    T value;
    int *order;
    NodeH* next;
public:
    /**
     * Constructor de la clase Node.
     */
    NodeH()
    {
        this->next= nullptr;
    }
    /**
     * Constructor alterno de la clase Node.
     * @param v Valor a almacenar.
     * @param o Identificador del nodo.
     */
    NodeH(T v,int o)
    {
        this->value=v;
        this->order=new int(o);
        this->next= nullptr;
    }
    /**
     * Metodo para obtener el valor que alamacena el nodo.
     * @return Valor almacenado.
     */
    T getValue()
    {
        return value;
    }
    /**
     * Metodo para obetener el nodo siguiente al nodo actual.
     * @return Nodo siguiente.
     */
    NodeH* getNext()
    {
        return next;
    }
    /**
     * Metodo para establecer el nodo siguiente al nodo actual.
     * @param node Nodo siguiente.
     */
    void setNext(NodeH<T>* node)
    {
        this->next=node;
    }
    /**
     * Metodo para obtner el identificador del nodo.
     * @return Identificador del nodo.
     */
    int getOrder()
    {
        return *this->order;
    }
    /**
     * Metodo para borrar todos los valores almacenados en el nodo.
     */
    void purge()
    {
        delete(this->order);
        this->value= nullptr;
        this->next= nullptr;
    }
    /**
     * Metodo para establecer el identificador del nodo.
     * @param o Identificador del nodo.
     */
    void setOrder(int o)
    {
        *this->order=o;
    }
};


#endif //MYDATABASE_NODEH_H
