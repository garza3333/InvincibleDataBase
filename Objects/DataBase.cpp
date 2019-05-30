//
// Created by Daniel on 26/05/2019.
//

#include <sstream>
#include "DataBase.h"


DataBase::DataBase() {
    this->MainList = new LinkedList<Image>();
    this->jManager = new JManager();

}

LinkedList<Image> *DataBase::getMainList() {
    return this->MainList;
}


void DataBase::insertImage(string name, string aut, int age, int size, string description) {
    MainList->add(Image(name, aut , age , size ,description));
}

void DataBase::insertImage(string atributes , string values) {
    vector<string> atributVector = this->split(atributes,'@');
    vector<string> valueVector = this->split(values,'@');

    string name = "default",author = "none",description = "nothing to describe";
    int year = 0,size = 0;

    for(int i = 0 ; i<atributVector.size() ; i++){
        string at = atributVector[i];
        if(at.compare("name") == 0){
            name = valueVector[i];
        }else if(at.compare("author") == 0){
            author = valueVector[i];
        }else if(at.compare("year") == 0){
            year = stoi(valueVector[i]);
        }else if(at.compare("size") == 0){
            size = stoi(valueVector[i]);
        }else if(at.compare("description") == 0){
            description = valueVector[i];
        }

    }
    MainList->add(Image(name,author,year,size,description));
}

void DataBase::insertImage(string json) {
    ptree ptImage = jManager->stringToPtree(json);
    string name = ptImage.get<string>("Name");
    string author = ptImage.get<string>("Author");
    int year = stoi(ptImage.get<string>("Year"));
    int size = stoi(ptImage.get<string>("Size"));
    string description = ptImage.get<string>("Description");


    MainList->add(Image(name,author,year,size,description));

}

vector<string> DataBase::split(string word, char delim) {
    vector<string> vec;
        std::stringstream ss(word);
        std::string token;
        while (std::getline(ss, token, delim)) {
            vec.push_back(token);}
        return vec;

}

ptree DataBase::findAll(string atributes, string values) {
    vector<string> atributVector = this->split(atributes,'@');
    vector<string> valueVector = this->split(values,'@');
    Node<Image> * temp = MainList->getHead();
    ptree pt;
    int cont = 0;
    while(temp != NULL){

        if(std::find(valueVector.begin(), valueVector.end(), temp->getValue().getName()) != valueVector.end()
        || std::find(valueVector.begin(), valueVector.end(), temp->getValue().getAuthor()) != valueVector.end()
        || std::find(valueVector.begin(), valueVector.end(), temp->getValue().getAuthor()) != valueVector.end()
        || std::find(valueVector.begin(), valueVector.end(), temp->getValue().getYear()) != valueVector.end()
        || std::find(valueVector.begin(), valueVector.end(), temp->getValue().getSize()) != valueVector.end()
        || std::find(valueVector.begin(), valueVector.end(), temp->getValue().getDescription()) != valueVector.end()) {
            ptree image;
            if(std::find(atributVector.begin(), atributVector.end(), "Name") != atributVector.end()){
                image.put("name",temp->getValue().getName());
            }else if(std::find(atributVector.begin(), atributVector.end(), "Author") != atributVector.end()){
                image.put("author",temp->getValue().getAuthor());
            }else if(std::find(atributVector.begin(), atributVector.end(), "Year") != atributVector.end()){
                image.put("year",temp->getValue().getYear());
            }else if(std::find(atributVector.begin(), atributVector.end(), "Size") != atributVector.end()){
                image.put("size",temp->getValue().getSize());
            }else if(std::find(atributVector.begin(), atributVector.end(), "Description") != atributVector.end()){
                image.put("description",temp->getValue().getDescription());
            }
            pt.put("Image"+to_string(cont),jManager->ptreeToString(image));
            cont++;
        }


        temp = temp->getNext();
    }
    jManager->printJson(pt);
    return pt;


}



