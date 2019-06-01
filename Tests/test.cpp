//
// Created by garza on 01/06/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Structures2/LinkedList.h"
#include "../Objects/DataBase.h"

using  testing::Eq;

namespace {
class ClassDeclaration : public testing::Test{
public:
    LinkedList<int> obj;

    ClassDeclaration(){
        obj;
    }
};
}


TEST_F(ClassDeclaration , insertInt){
    auto * l = new LinkedList<int>();
    l->add(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->addFirst(0);

    l->delNode(1);
    l->delNode(0);
    l->delNode(5);

    EXPECT_EQ(l->getSize() , 3);
}
TEST_F(ClassDeclaration , isIn){
    auto * l = new LinkedList<int>();
    l->add(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->addFirst(0);

    l->delNode(1);
    l->delNode(0);
    l->delNode(5);

    EXPECT_TRUE(l->in(2));
}

TEST_F(ClassDeclaration , vectorSplit){

    DataBase db = DataBase();
    vector<string> vec = db.split("name@author@year",'@');
    string final = vec[0]+vec[1]+vec[2];
    EXPECT_EQ("nameauthoryear",final);

}

TEST_F(ClassDeclaration , addEmpty){

    DataBase db = DataBase();
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
    EXPECT_FALSE(db.insertImage(jm.ptreeToString(pt)));


}

TEST_F(ClassDeclaration , foundGalery){
    DataBase db = DataBase();
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
    db.addGalery("nose");
    EXPECT_FALSE(db.insertImage(jm.ptreeToString(pt)));
}
TEST_F(ClassDeclaration , notfoundGalery){
    DataBase db = DataBase();
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
    db.addGalery("Photos");
    EXPECT_TRUE(db.insertImage(jm.ptreeToString(pt)));

}