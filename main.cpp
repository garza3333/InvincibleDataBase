#include <iostream>
#include "Structures/LinkedList.h"
#include "Objects/DataBase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//includes for directories
#include <dirent.h> //mkdir






int main(int argc , char * argv[]) {

    //testing::InitGoogleTest(&argc , argv);
    //RUN_ALL_TESTS();

    DataBase * db = new DataBase();
    db->addGalery("Photos");
    JManager jm = JManager();
    cout<<endl;

    //IMAGEN 1
    ptree pt;
    pt.put("FROM","Photos");
    pt.put("ATRIBUTES","name,author,description,year,size");
    pt.put("name","danielImage");
    pt.put("author","GARZA");
    pt.put("size","3");
    pt.put("year","2019");
    pt.put("description","its a test image");

    //IMAGEN2
    ptree pt2;
    pt2.put("FROM","Photos");
    pt2.put("ATRIBUTES","name,description,size,author");
    pt2.put("name","danielImage");
    pt2.put("author","SOFIA");
    pt2.put("size","1023");
    pt2.put("description","this shit");


    db->insertImage(jm.ptreeToString(pt));
    db->insertImage(jm.ptreeToString(pt2));

    ptree selectPT;
    selectPT.put("FROM","Photos");
    selectPT.put("SELECT","name,author,description");
    selectPT.put("name","danielImage");

    jm.printJson(db->selectImage(jm.ptreeToString(selectPT)));


    /*string root = "../Master";

    string ruta = root + "/holanueva";
    if(mkdir(ruta.c_str() ,0777)==0){
        cout<<"carpeta correctamente creada"<<endl;
    }else{
        cout<<"carpeta no creada"<<endl;
    }*/

    db->addGalery("Galeria1");
    db->addGalery("GARAZGALERY");
    db->addGalery("carpetitagalery");
    db->showDirs();
    db->saveToDisk();




    return 0;

}