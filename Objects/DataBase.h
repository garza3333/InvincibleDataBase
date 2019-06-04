//
// Created by Daniel on 26/05/2019.
//

#ifndef MYDATABASE_DATABASE_H
#define MYDATABASE_DATABASE_H


#include "Image.h"
#include "../Structures2/LinkedList.h"
#include "JManager.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using boost::property_tree::ptree;
using  namespace std;
class DataBase {


private:
    LinkedList<LinkedList<Image>*> * MainList;
    JManager * jManager;

public:
    /**
     * Builder of the class
     */
    DataBase();
    LinkedList<LinkedList<Image>*> * getMainList();
    bool addGalery(string nameGalery);
    bool insertImage(string json);
    ptree selectImage(string json);
    ptree fillPtreeImage(Node<Image> * image, vector<string> atributeVEC);
    //ptree findAll(string atributes , string values );

    vector<string> split(string word , char delim);


};


#endif //MYDATABASE_DATABASE_H
