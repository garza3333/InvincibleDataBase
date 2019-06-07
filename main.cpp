#include <iostream>
#include "Structures/LinkedList.h"
#include "Objects/DataBase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//includes for directories
#include <dirent.h> //mkdir
#include <string>
#include <string.h>
#include <algorithm>





using namespace std;
int main(int argc , char * argv[]) {

    //testing::InitGoogleTest(&argc , argv);
    //RUN_ALL_TESTS();
    JManager jsonM = JManager();
    DataBase * dataB = new DataBase();
    dataB->addGalery("Photos");
    cout<<endl;

    //IMAGEN 1
    ptree pt;
    pt.put("INTO","Photos");
    pt.put("ATRIBUTES","name,author,description,year,size");
    pt.put("name","danielImage");
    pt.put("author","GARZA");
    pt.put("size","3");
    pt.put("year","2019");
    pt.put("description","its a test image");

    //IMAGEN2
    ptree pt2;
    pt2.put("INTO","Photos");
    pt2.put("ATRIBUTES","name,description,size,author,year");
    pt2.put("name","danielImage");
    pt2.put("author","SOFIA");
    pt2.put("year","2018");
    pt2.put("size","2000");
    pt2.put("description","this shit");

    //IMAGEN3
    ptree pt3;
    pt3.put("INTO","Photos");
    pt3.put("ATRIBUTES","name,description,size,author,year");
    pt3.put("name","gabriel");
    pt3.put("author","GARZA");
    pt3.put("year","2019");
    pt3.put("size","2000");
    pt3.put("description","this is a description");

    //IMAGEN4
    ptree pt4;
    pt4.put("INTO","Photos");
    pt4.put("ATRIBUTES","name,description,size,author,year");
    pt4.put("name","danielImage");
    pt4.put("author","SOFIA");
    pt4.put("year","2019");
    pt4.put("size","1023");
    pt4.put("description","i need coffee");


    dataB->insertImage(jsonM.ptreeToString(pt));
    dataB->insertImage(jsonM.ptreeToString(pt2));
    dataB->insertImage(jsonM.ptreeToString(pt3));
    dataB->insertImage(jsonM.ptreeToString(pt4));

    //find -> name = danielImage
    ptree selectPT;
    selectPT.put("FROM","Photos");
    selectPT.put("SELECT","name,author,description,year");
    selectPT.put("name","danielImage");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT)));
    //find -> size = 2000
    ptree selectPT1;
    selectPT1.put("FROM","Photos");
    selectPT1.put("SELECT","name,author,description,year,size");
    selectPT1.put("size","2000");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT1)));

    //find -> year = 2019
    ptree selectPT2;
    selectPT2.put("FROM","Photos");
    selectPT2.put("SELECT","name,author,description,year,size");
    selectPT2.put("year","2019");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT2)));

    //find -> year = 2019
    //find -> name = danielImage
    ptree selectPT3;
    selectPT3.put("FROM","Photos");
    selectPT3.put("SELECT","name,author,description,year,size");
    selectPT3.put("year","2019");
    selectPT3.put("name","danielImage");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT3)));


    //find -> author = GARZA
    ptree selectPT4;
    selectPT4.put("FROM","Photos");
    selectPT4.put("SELECT","name,author,description,year,size");
    selectPT4.put("author","GARZA");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT4)));

    ptree updatept;
    updatept.put("UPDATE","Photos");
    updatept.put("SET","name = danielImage,author = SOFIA");
    updatept.put("name","gabriel");

/*    dataB->updateImage(jsonM.ptreeToString(updatept));

    //find -> author = SOFIA
    ptree selectPT5;
    selectPT5.put("FROM","Photos");
    selectPT5.put("SELECT","name,author,description,year,size");
    selectPT5.put("author","SOFIA");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT5)));*/










    dataB->addGalery("galeria1");
    dataB->addGalery("galeria2");
    dataB->addGalery("galeria3");

    dataB->saveToDisk();







    return 0;

}