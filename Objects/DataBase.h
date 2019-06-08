//
// Created by Daniel on 26/05/2019.
//

#ifndef MYDATABASE_DATABASE_H
#define MYDATABASE_DATABASE_H


#include "Image.h"
#include "../Structures/LinkedList.h"
#include "JManager.h"
#include "../Compressor/Compressor.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>


//includes for directories
#include <dirent.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>


using boost::property_tree::ptree;
using  namespace std;
class DataBase {


private:
    LinkedList<LinkedList<Image*>*> * MainList;
    Compressor * compressor;
    JManager * jManager;
    string root;
    int imageID;

public:
    /**
     * Builder of the class
     */
    DataBase();
    string getRoot();
    void setRoot(string newRoot);
    LinkedList<LinkedList<Image*>*> * getMainList();
    bool addGalery(string nameGalery);
    bool deleteGalery(string galery);
    bool insertImage(string json);
    bool updateImage(string json);
    bool deleteImage(string json);
    ptree selectImage(string json);
    static ptree fillPtreeImage(NodeHuff<Image*> * image, vector<string> atributeVEC);
    vector<string> split(string word , char delim);
    void saveToDisk();
    void loadInMemory();
    void showDirs();
    void showALLImages(string galery);
    void compressData(string json , string galery);
    string descompressData(string galery , string tree , string code);


};


#endif //MYDATABASE_DATABASE_H
