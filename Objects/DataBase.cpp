//
// Created by Daniel on 26/05/2019.
//


#include "DataBase.h"


DataBase::DataBase() {

    this->MainList = new LinkedList<LinkedList<Image>>();
    this->jManager = new JManager();

}

LinkedList<LinkedList<Image>> *DataBase::getMainList() {
    return this->MainList;
}

bool DataBase::addGalery(string nameGalery) {

    if(MainList->add(LinkedList<Image>(nameGalery))){
        return true;
    }else{
        return false;
    }

}

bool DataBase::insertImage(string json) {
    if(!MainList->isEmpty()) {

        ptree ptImage = jManager->stringToPtree(json);
        string galery = ptImage.get<string>("FROM");
        MainList->setTemp(MainList->getHead());

        while (MainList->getTemp() != NULL && MainList->getTemp()->getValue().getID() != galery) {

            MainList->setTemp(MainList->getTemp()->getNext());

        }

        if(MainList->getTemp() == NULL){
            cout<<"No se encontró la galeria, no se añadió imagen";
            return false;
        }else{

            string name = "default", author = "none", description = "nothing to describe";
            int year = 0, size = 0;

            vector<string> atributVector = split(ptImage.get<string>("ATRIBUTES"), ',');
            for (int i = 0; i < atributVector.size(); i++) {
                string at = atributVector[i];
                if (at.compare("name") == 0) {
                    name = ptImage.get<string>("name");
                } else if (at.compare("author") == 0) {
                    author = ptImage.get<string>("author");
                } else if (at.compare("year") == 0) {
                    year = stoi(ptImage.get<string>("year"));
                } else if (at.compare("size") == 0) {
                    size = stoi(ptImage.get<string>("size"));
                } else if (at.compare("description") == 0) {
                    description = ptImage.get<string>("description");
                }

            }


            MainList->getTemp()->getValue().add(Image(name, author, year, size, description));
            cout<<"the image has been added!"<<endl;
            return true;
        }

    }else{
        cout<<"the list is empty! "<<endl;
        return false;
    }


}

vector<string> DataBase::split(string word, char delim) {
    vector<string> vec;
        std::stringstream ss(word);
        std::string token;
        while (std::getline(ss, token, delim)) {
            vec.push_back(token);}
        return vec;

}

/*ptree DataBase::findAll(string atributes, string values) {
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


}*/



