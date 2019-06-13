#include <iostream>
#include "Structures/LinkedList.h"
#include "Objects/DataBase.h"
#include "Compressor/Compressor.h"
#include "Compressor/List.h"
#include "Compressor/NodeH.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//includes for directories
#include <dirent.h> //mkdir
#include <string>
#include <string.h>
#include <algorithm>
#include "server/requestHandler.h"


using namespace std;
int main(int argc , char * argv[]) {

    //testing::InitGoogleTest(&argc , argv);
    //RUN_ALL_TESTS();


/*    JManager jsonM = JManager();
    auto comp = new Compressor();
    DataBase * dataB = new DataBase();
    dataB->addGalery("Photos");
    cout<<endl;

    //IMAGEN 1
    ptree pt;
    pt.put("table","Photos");
    pt.put("cols","name,author,description,year,size");
    pt.put("values","danielImage,GARZA,its a test image,2019,3");


    //IMAGEN2
    ptree pt2;
    pt2.put("table","Photos");
    pt2.put("cols","name,description,size,author,year");
    pt2.put("values","danielImage,this shit,2000,SOFIA,2018");


    //IMAGEN3
    ptree pt3;
    pt3.put("table","Photos");
    pt3.put("cols","name,description,size,author,year");
    pt3.put("values","gabriel,this is a description,2000,GARZA,2019");


    //IMAGEN4
    ptree pt4;
    pt4.put("table","Photos");
    pt4.put("cols","name,description,size,author,year");
    pt4.put("values","danielImage,i need coffee,1023,SOFIA,2019");


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

    //find -> author = SOFIA
    ptree selectPT5;
    selectPT5.put("FROM","Photos");
    selectPT5.put("SELECT","name,author,description,year,size");
    selectPT5.put("author","SOFIA");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT5)));

    ptree updatept;
    updatept.put("UPDATE","Photos");
    updatept.put("SET","name = DAVID,author = SOFIA");
    updatept.put("name","gabriel");

    dataB->updateImage(jsonM.ptreeToString(updatept));

    //find -> author = SOFIA
    ptree selectPT6;
    selectPT6.put("FROM","Photos");
    selectPT6.put("SELECT","name,author,description,year,size");
    selectPT6.put("author","SOFIA");
    jsonM.printJson(dataB->selectImage(jsonM.ptreeToString(selectPT6)));

    cout<<"PHOTOS"<<endl;
    dataB->showALLImages("Photos");


    dataB->addGalery("galeria1");
    dataB->addGalery("galeria2");
    dataB->addGalery("galeria3");

    dataB->deleteGalery("galeria1");
    dataB->deleteGalery("galeria3");
    dataB->showDirs();
    dataB->saveToDisk();*/


    //PRUEBA PARA INICIALIZAR EL IDLE

/*    ptree prueba;
    ptree Galery;
    ptree ima1;
    ptree ima2;


    ima1.put("name","sing");
    ima1.put("author","GARZA");
    ima1.put("year","2019");
    ima1.put("size","2000");
    ima1.put("description","this is a description");

    ima2.put("name","daniel");
    ima2.put("author","DAVID");
    ima2.put("year","2017");
    ima2.put("size","3000");
    ima2.put("description","fucking shit");

    Galery.put("NumImages",2);
    Galery.put("Name","Photos");
    Galery.put("Image0",jsonM.ptreeToString(ima1));
    Galery.put("Image1",jsonM.ptreeToString(ima2));


    prueba.put("NUM",1);
    prueba.put("Galery0",jsonM.ptreeToString(Galery));

    string s = jsonM.ptreeToString(prueba);

    vector<char> ch;
    for(int i=0;i<s.size();i++)
    {
        ch.push_back(s.at(i));
    }
    Compressor::Codified_File * code = comp->compress(ch,"txt","../Master/compress");
    Compressor::Decodified_File
    * decode = comp->decompress(code);
    comp->writeToDiskComp(code);
    comp->writeToDiskDecomp(decode);*/

/*    cout<<"\nINIT TREE "<<endl;
    cout<<dataB->initIdleTree()<<endl;*/





// SERVIDOR

    Address addr(Ipv4::any(), Port(9082));
    auto opts = Http::Endpoint::options()
            .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<requestHandler>());
    server.serve();

    server.shutdown();

    return 0;

}