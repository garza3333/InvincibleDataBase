//
// Created by Daniel on 26/05/2019.
//


#include "DataBase.h"


DataBase::DataBase() {

    this->MainList = new LinkedList<LinkedList<Image>*>();
    this->jManager = new JManager();
    this->root = "../Master/";

}

string DataBase::getRoot() {
    return this->root;
}

void DataBase::setRoot(string newRoot) {
    this->root = "../"+newRoot+"/";
}

LinkedList<LinkedList<Image>*> *DataBase::getMainList() {
    return this->MainList;
}

bool DataBase::addGalery(string nameGalery) {
    LinkedList<Image> * newGalery =  new LinkedList<Image>(nameGalery);
    return MainList->add(newGalery);

}

bool DataBase::insertImage(string json) {
    if(!MainList->isEmpty()) {

        ptree ptImage = jManager->stringToPtree(json);
        string galery = ptImage.get<string>("FROM");
        MainList->setTemp(MainList->getHead());

        while (MainList->getTemp() != NULL && MainList->getTemp()->getValue()->getID() != galery) {

            MainList->setTemp(MainList->getTemp()->getNext());

        }

        if(MainList->getTemp() == NULL){
            cout<<"Gallery not found , image not added ";
            return false;
        }else{

            string name = "NULL", author = "NULL", description = "NULL";
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

            Image newImage = Image(name, author, year, size, description);

            MainList->getTemp()->getValue()->add(newImage);
            cout<<"The image has been added!"<<endl;
            return true;
        }

    }else{
        cout<<"The list is empty! "<<endl;
        return false;
    }

}

ptree DataBase::selectImage(string json) {
    ptree ptImage = jManager->stringToPtree(json);
    string from = ptImage.get<string>("FROM");

    MainList->setTemp(MainList->getHead());

    while(MainList->getTemp() != NULL && MainList->getTemp()->getValue()->getID() != from){
        MainList->setTemp(MainList->getTemp()->getNext());
    }
    if(MainList->getTemp() == NULL){
        cout<<"No se encontró una galeria con el nombre <<"<<from<<">>";

    }else{
        ptree imagesJson;
        MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
        //vector<string> valuesVEC = this->split(ptImage.get<string>("WHERE"),',');
        vector<string> atributesVEC = this->split(ptImage.get<string>("SELECT"),',');
        int cont = 0;
        while(MainList->getTemp()->getValue()->getTemp() != NULL){

            //TODO : preguntarle a david si con formato name,author o name:name author:author
            if(ptImage.get<string>("name") == MainList->getTemp()->getValue()->getTemp()->getValue().getName()
            || ptImage.get<string>("author") == MainList->getTemp()->getValue()->getTemp()->getValue().getAuthor()
            || stoi(ptImage.get<string>("year")) == MainList->getTemp()->getValue()->getTemp()->getValue().getYear()
            || stoi(ptImage.get<string>("size")) == MainList->getTemp()->getValue()->getTemp()->getValue().getSize()
            || ptImage.get<string>("description") == MainList->getTemp()->getValue()->getTemp()->getValue().getDescription()){

                imagesJson.put("Image"+to_string(cont),jManager->ptreeToString(this->fillPtreeImage(MainList->getTemp()->getValue()->getTemp(),atributesVEC)));
                cont++;
            }
            MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());

        }
        return imagesJson;
    }
}

bool DataBase::updateImage() {
    return false;
}

bool DataBase::deleteImage() {
    return false;
}

ptree DataBase::fillPtreeImage(Node<Image> *image, vector<string> vec) {

    ptree ptim;
    for (int i = 0; i < vec.size(); i++) {
        string at = vec[i];
        if (at.compare("name") == 0) {
            ptim.put("name",image->getValue().getName());
        } else if (at.compare("author") == 0) {
            ptim.put("author",image->getValue().getAuthor());
        } else if (at.compare("year") == 0) {
            ptim.put("year",image->getValue().getYear());
        } else if (at.compare("size") == 0) {
            ptim.put("size",image->getValue().getSize());
        } else if (at.compare("description") == 0) {
            ptim.put("description",image->getValue().getDescription());
        }

    }

    return ptim;
}

vector<string> DataBase::split(string word, char delim) {

    vector<string> vec;
    std::stringstream ss(word);
    std::string token;
    while (std::getline(ss, token, delim)) {
        vec.push_back(token);}
    return vec;

}

void DataBase::saveToDisk() {
    if(MainList->isEmpty()){
        cout<<"NO hay ninguna galeria para ser creada";
    }else {
        vector<string> folders;
        vector<string> foldersNot;
        MainList->setTemp(MainList->getHead());

        while (MainList->getTemp() != NULL) {

            string newFolder = this->root + MainList->getTemp()->getValue()->getID();
            if (mkdir(newFolder.c_str(), 0777) == 0) {
                MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
                ptree allImages;
                int cont = 0;
                while(MainList->getTemp()->getValue()->getTemp() != NULL){
                    ptree image;
                    image.put("name",MainList->getTemp()->getValue()->getTemp()->getValue().getName());
                    image.put("author",MainList->getTemp()->getValue()->getTemp()->getValue().getAuthor());
                    image.put("year",MainList->getTemp()->getValue()->getTemp()->getValue().getYear());
                    image.put("size",MainList->getTemp()->getValue()->getTemp()->getValue().getSize());
                    image.put("description",MainList->getTemp()->getValue()->getTemp()->getValue().getDescription());
                    allImages.put("Image"+to_string(cont),jManager->ptreeToString(image));
                    cont++;
                    MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());
                }
                //TODO: Aqui iria la creacion del archivo se debe crear la ruta con el temp
                ofstream file;
                file.open(root+MainList->getTemp()->getValue()->getID()+"/MetaData.txt");
                file << jManager->ptreeToString(allImages);
                file.close();
                folders.push_back(MainList->getTemp()->getValue()->getID());
            } else {
                MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
                ptree allImages;
                int cont = 0;
                while(MainList->getTemp()->getValue()->getTemp() != NULL){
                    ptree image;
                    image.put("name",MainList->getTemp()->getValue()->getTemp()->getValue().getName());
                    image.put("author",MainList->getTemp()->getValue()->getTemp()->getValue().getAuthor());
                    image.put("year",MainList->getTemp()->getValue()->getTemp()->getValue().getYear());
                    image.put("size",MainList->getTemp()->getValue()->getTemp()->getValue().getSize());
                    image.put("description",MainList->getTemp()->getValue()->getTemp()->getValue().getDescription());
                    allImages.put("Image"+to_string(cont),jManager->ptreeToString(image));
                    cont++;
                    MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());
                }
                //TODO: Aqui iria la creacion del archivo pero hay que crear la ruta con el temp
                ofstream file;
                file.open(root+MainList->getTemp()->getValue()->getID()+"/MetaData.txt");
                file << jManager->ptreeToString(allImages);
                file.close();
                foldersNot.push_back(MainList->getTemp()->getValue()->getID());
            }
            MainList->setTemp(MainList->getTemp()->getNext());
        }
        cout<<"-- Carpetas creadas:"<<"\n"<<endl;
        for(int i = 0 ; i<folders.size() ; i++){
            cout<<"-> "<<folders[i]<<endl;
        }cout<<endl;
        cout<<"-- Carpetas NO creadas:"<<"\n"<<endl;
        for(int j = 0 ; j<foldersNot.size() ; j++){
            cout<<"-> "<<foldersNot[j]<<endl;
        }
    }

}

void DataBase::loadInMemory() {

}

void DataBase::showDirs() {
    if(!MainList->isEmpty()){

        MainList->setTemp(MainList->getHead());
        cout<<"[";
        while(MainList->getTemp()->getNext() != NULL){

            cout<<MainList->getTemp()->getValue()->getID()<<",";
            MainList->setTemp(MainList->getTemp()->getNext());
        }MainList->setTemp(MainList->getTemp());
        cout<<MainList->getTemp()->getValue()->getID()<<"]"<<endl;
    }else{
        cout<<"[]"<<endl;
    }

}


