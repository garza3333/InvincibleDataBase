#include <iostream>
#include "Structures2/LinkedList.h"
#include "Objects/DataBase.h"

int main() {
/*    auto * l = new LinkedList<int>();
    l->add(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->addFirst(0);
    l->see();
    l->delNode(1);
    l->delNode(0);
    l->delNode(5);
    l->see();
    if(l->in(2)){
        cout<<"true"<<endl;
    }*/
    DataBase db = DataBase();
/*    vector<string> vec = db.split("name@author@year",'@');
    for(int i = 0 ; i<vec.size() ; i++){
        cout<<vec[i]<<endl;
    }*/
    cout<<endl;
    db.insertImage("author@name@size@year","daniel@NuevaImagen@78@2019");
    cout<<"insert: "<<"author@name@size@year"<<endl;
    cout<<"values: "<<"daniel@NuevaImagen@78@2019"<<endl;
    Image i = db.getMainList()->getHead()->getValue();
    cout<<"name: "<<i.getName()<<endl;
    cout<<"author: "<<i.getAuthor()<<endl;
    cout<<"year: "<<i.getYear()<<endl;
    cout<<"size: "<<i.getSize()<<endl;
    cout<<"description: "<<i.getDescription()<<endl;


/*    BST t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.insert(5);
    t.insert(35);
    t.insert(67);
    t.insert(43);
    t.insert(21);
    t.insert(10);
    t.insert(89);
    t.insert(38);
    t.insert(69);
    t.display();
    t.remove(5);
    t.remove(35);
    t.remove(65);
    t.remove(89);
    t.remove(43);
    t.remove(88);
    t.remove(20);
    t.remove(38);
    t.display();*/

    return 0;

}