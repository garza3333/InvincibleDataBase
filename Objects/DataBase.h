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

using namespace std;
class DataBase {


private:
    LinkedList<Image> * MainList;
    JManager * jManager;

public:
    /**
     * Builder of the class
     */
    DataBase();
    LinkedList<Image> * getMainList();
    /**
     * Insert a image to the linkedList
     * @param name image name
     * @param aut author name
     * @param age year of publication
     * @param size size of the image
     * @param description description of the image
     * @return
     */
    void insertImage(string name , string aut , int age , int size , string description );
    void insertImage(string atributes , string values);
    void insertImage(string json);
    ptree findAll(string atributes , string values );

    vector<string> split(string word , char delim);


};


#endif //MYDATABASE_DATABASE_H
