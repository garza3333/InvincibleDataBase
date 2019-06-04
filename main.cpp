#include <iostream>
#include "Structures2/LinkedList.h"
#include "Objects/DataBase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
int main(int argc , char * argv[]) {

    //testing::InitGoogleTest(&argc , argv);
    //RUN_ALL_TESTS();

    DataBase * db = new DataBase();
    db->addGalery("Photos");
    JManager jm = JManager();
    cout<<endl;
    ptree pt;
    pt.put("FROM","Photos");
    pt.put("ATRIBUTES","name,author,description,year,size");
    pt.put("name","danielImage");
    pt.put("author","GARZA");
    pt.put("size","3");
    pt.put("year","2019");
    pt.put("description","its a test image");


    ptree pt2;
    pt2.put("FROM","Photos");
    pt2.put("ATRIBUTES","name,description,size,author");
    pt2.put("name","danielImage");
    pt2.put("author","SOFIA");
    pt2.put("size","1023");
    pt2.put("description","this shit");

    string ptstring = jm.ptreeToString(pt);
    db->insertImage(ptstring);7
    string ptstring2 = jm.ptreeToString(pt2);
    db->insertImage(ptstring2);

    ptree selectPT;
    selectPT.put("FROM","Photos");
    selectPT.put("SELECT","name,author,description");
    selectPT.put("name","danielImage");

    string stringMessage = jm.ptreeToString(selectPT);

    ptree jsonMessage = db->selectImage(stringMessage);
    jm.printJson(jsonMessage);


/*    Node<Image> * node = db->getMainList()->getHead()->getValue()->getHead();
    cout<<node->getValue().getName()<<endl;
    cout<<node->getValue().getAuthor()<<endl;
    cout<<node->getValue().getYear()<<endl;
    cout<<node->getValue().getSize()<<endl;
    cout<<node->getValue().getDescription()<<endl;

    Node<Image> * node2 = db->getMainList()->getHead()->getValue()->getHead()->getNext();
    cout<<node2->getValue().getName()<<endl;
    cout<<node2->getValue().getAuthor()<<endl;
    cout<<node2->getValue().getYear()<<endl;
    cout<<node2->getValue().getSize()<<endl;
    cout<<node2->getValue().getDescription()<<endl;*/











    /*db.insertImage("author@name@size@year","daniel@NuevaImagen@78@2019");
    cout<<"insert: "<<"author@name@size@year"<<endl;
    cout<<"values: "<<"daniel@NuevaImagen@78@2019"<<endl;*/
   /* ptree pt;
    pt.put("name")
    Image i = db.getMainList()->getHead()->getValue();
    cout<<"name: "<<i.getName()<<endl;
    cout<<"author: "<<i.getAuthor()<<endl;
    cout<<"year: "<<i.getYear()<<endl;
    cout<<"size: "<<i.getSize()<<endl;
    cout<<"description: "<<i.getDescription()<<endl;*/



    return 0;

}