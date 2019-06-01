#include <iostream>
#include "Structures2/LinkedList.h"
#include "Objects/DataBase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
int main(int argc , char * argv[]) {

    testing::InitGoogleTest(&argc , argv);
    RUN_ALL_TESTS();






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