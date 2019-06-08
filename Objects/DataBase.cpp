//
// Created by Daniel on 26/05/2019.
//


#include "DataBase.h"


DataBase::DataBase() {

    this->MainList = new LinkedList<LinkedList<Image*>*>();
    this->jManager = new JManager();
    this->root = "../Master/";

    ifstream inFile;
    inFile.open("../Master/imagesID.txt");

    if (inFile.is_open()) {

        string line;
        getline(inFile,line);
        this->imageID = stoi(line);
        cout<<"imagesID: "<<this->imageID<<endl;
        inFile.close();
    }else{
        cout << "Cant pen the file";
        this->imageID = 0;
    }


}

string DataBase::getRoot() {
    return this->root;
}

void DataBase::setRoot(string newRoot) {
    this->root = "../"+newRoot+"/";
}

LinkedList<LinkedList<Image*>*> *DataBase::getMainList() {
    return this->MainList;
}

bool DataBase::addGalery(string nameGalery) {
    LinkedList<Image*> * newGalery =  new LinkedList<Image*>(nameGalery);
    return MainList->add(newGalery);

}

bool DataBase::deleteGalery(string galery) {

    if(!MainList->isEmpty()){
        NodeHuff<LinkedList<Image*> *> * delPtr = nullptr;

        MainList->setTemp(MainList->getHead());
        MainList->setCurr(MainList->getHead());
        if(MainList->getCurr()->getValue()->getID() == galery){
            delPtr = MainList->getHead();
            MainList->setHEAD(MainList->getHead()->getNext());
            delPtr->setNext(nullptr);
            delete delPtr;
            MainList->substractSize();
            return true;
        }
        while(MainList->getCurr() != nullptr && MainList->getCurr()->getValue()->getID() != galery){
            MainList->setTemp(MainList->getCurr());
            MainList->setCurr(MainList->getCurr()->getNext());
        }
        if(MainList->getCurr() == nullptr){
            cout<<"Galery not found to delete"<<endl;
            delete delPtr;
            return false;
        }else{
            MainList->getTemp()->setNext(MainList->getCurr()->getNext());
            MainList->getCurr()->setNext(nullptr);
            delPtr = MainList->getCurr();
            delete delPtr;
            MainList->substractSize();
            return true;
        }
    }

}

bool DataBase::insertImage(string json) {
    if(!MainList->isEmpty()) {

        ptree ptImage = jManager->stringToPtree(json);
        string galery = ptImage.get<string>("INTO");
        MainList->setTemp(MainList->getHead());

        while (MainList->getTemp() != nullptr && MainList->getTemp()->getValue()->getID() != galery) {

            MainList->setTemp(MainList->getTemp()->getNext());

        }

        if(MainList->getTemp() == nullptr){
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

            Image * newImage = new Image(name, author, year, size, description , this->imageID);
            this->imageID++;

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

    while(MainList->getTemp() != nullptr && MainList->getTemp()->getValue()->getID() != from){
        MainList->setTemp(MainList->getTemp()->getNext());
    }
    if(MainList->getTemp() == nullptr){
        cout<<"No se encontró una galeria con el nombre <<"<<from<<">>";

    }else{
        ptree imagesJson;
        MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
        //vector<string> valuesVEC = this->split(ptImage.get<string>("WHERE"),',');
        vector<string> atributesVEC = this->split(ptImage.get<string>("SELECT"),',');
        int cont = 0;
        while(MainList->getTemp()->getValue()->getTemp() != nullptr){

            //TODO : preguntarle a david si con formato name,author o name:name author:author
            if(ptImage.get_optional<string>("name") == MainList->getTemp()->getValue()->getTemp()->getValue()->getName()
            || ptImage.get_optional<string>("author") == MainList->getTemp()->getValue()->getTemp()->getValue()->getAuthor()
            || ptImage.get_optional<string>("year") == to_string(MainList->getTemp()->getValue()->getTemp()->getValue()->getYear())
            || ptImage.get_optional<string>("size") == to_string(MainList->getTemp()->getValue()->getTemp()->getValue()->getSize())
            || ptImage.get_optional<string>("description") == MainList->getTemp()->getValue()->getTemp()->getValue()->getDescription()){

                imagesJson.put("Image"+to_string(cont),jManager->ptreeToString(this->fillPtreeImage(MainList->getTemp()->getValue()->getTemp(),atributesVEC)));
                cont++;
            }
            MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());

        }
        return imagesJson;
    }
}

bool DataBase::updateImage(string json) {
    ptree ptImage = jManager->stringToPtree(json);
    string from = ptImage.get<string>("UPDATE");
    MainList->setTemp(MainList->getHead());
    while(MainList->getTemp() != nullptr && MainList->getTemp()->getValue()->getID() != from){
        MainList->setTemp(MainList->getTemp()->getNext());
    }
    if(MainList->getTemp() == nullptr){
        cout<<"No se encontró la galeria >>"<<MainList->getTemp()->getValue()->getID()<<">>"<<endl;
        return false;

    }else{
        MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
        vector<string> setVEC = split(ptImage.get<string>("SET"),',');
        string name = "n-u*l-l";
        string author = "n-u*l-l";
        int year = -2;
        int size =-2;
        string description = "n-u*l-l";

        for(int i = 0 ; i<setVEC.size() ; i++ ){
            setVEC[i].erase(remove(setVEC[i].begin(), setVEC[i].end(), ' '), setVEC[i].end()); //delete the spaces ' '
            vector<string> set = split(setVEC[i],'=');
            if(set[0] == "name"){
                name = set[1];
            }else if(set[0] == "author"){
                author = set[1];
            }else if(set[0] == "year"){
                year = stoi(set[1]);
            }else if(set[0] == "size"){
                size = stoi(set[1]);
            }else if(set[0] == "description"){
                description = set[1];
            }
        }
        while(MainList->getTemp()->getValue()->getTemp() != nullptr){
            if(MainList->getTemp()->getValue()->getTemp()->getValue()->getName() == ptImage.get_optional<string>("name")
            ||MainList->getTemp()->getValue()->getTemp()->getValue()->getAuthor() == ptImage.get_optional<string>("author")
            ||to_string(MainList->getTemp()->getValue()->getTemp()->getValue()->getYear()) == ptImage.get_optional<string>("year")
            ||to_string(MainList->getTemp()->getValue()->getTemp()->getValue()->getSize()) == ptImage.get_optional<string>("size")
            ||MainList->getTemp()->getValue()->getTemp()->getValue()->getDescription() == ptImage.get_optional<string>("description")){
                //TODO: aqui van los ifs para saber que modificar
                if(name != "n-u*l-l"){
                    MainList->getTemp()->getValue()->getTemp()->getValue()->setName(name);
                }
                if(author != "n-u*l-l"){
                    MainList->getTemp()->getValue()->getTemp()->getValue()->setAuthor(author);
                }
                if(year != -2){
                    MainList->getTemp()->getValue()->getTemp()->getValue()->setYear(year);
                }
                if(size != -2){
                    MainList->getTemp()->getValue()->getTemp()->getValue()->setSize(size);
                }
                if(description != "n-u*l-l"){
                    MainList->getTemp()->getValue()->getTemp()->getValue()->setDescription(description);
                }
                MainList->getTemp()->getValue()->getTemp();
            }

            MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());
        }
        return true;


    }

}

bool DataBase::deleteImage(string json) {

    ptree imageJson = jManager->stringToPtree(json);
    MainList->setTemp(MainList->getHead());
    while(MainList->getTemp() != nullptr && MainList->getTemp()->getValue()->getID() != imageJson.get<string>("FROM")){
        MainList->setTemp(MainList->getTemp()->getNext());
    }
    if(MainList->getTemp() == nullptr){
        cout<<"Galery not found";
        return false;
    }else{

        string name = "n-u*l-l";
        string author = "n-u*l-l";
        int year = -2;
        int size = -2;
        string description = "n-u*l-l";
        vector<string> whereVEC = split(imageJson.get<string>("WHERE"),',');


        for(int i = 0 ; i<whereVEC.size() ; i++ ){
            whereVEC[i].erase(remove(whereVEC[i].begin(), whereVEC[i].end(), ' '), whereVEC[i].end()); //delete the spaces ' '
            vector<string> set = split(whereVEC[i],'=');
            if(set[0] == "name"){
                name = set[1];
            }else if(set[0] == "author"){
                author = set[1];
            }else if(set[0] == "year"){
                year = stoi(set[1]);
            }else if(set[0] == "size"){
                size = stoi(set[1]);
            }else if(set[0] == "description"){
                description = set[1];
            }
        }

        NodeHuff<Image*> * delPtr = nullptr;
        MainList->getTemp()->getValue()->setTemp(MainList->getHead()->getValue()->getHead());
        MainList->getTemp()->getValue()->setCurr(MainList->getTemp()->getValue()->getHead());

        if(MainList->getTemp()->getValue()->getCurr()->getValue()->getName() == name
           || MainList->getTemp()->getValue()->getCurr()->getValue()->getAuthor() == author
           || MainList->getTemp()->getValue()->getCurr()->getValue()->getYear() == year
           || MainList->getTemp()->getValue()->getCurr()->getValue()->getSize() == size
           || MainList->getTemp()->getValue()->getCurr()->getValue()->getDescription() == description){
            delPtr = MainList->getTemp()->getValue()->getHead();
            MainList->setHEAD(MainList->getHead()->getNext());
            delPtr->setNext(nullptr);
            delete delPtr;
            MainList->getTemp()->getValue()->substractSize();
            return this->deleteImage(json);
        }

        while(MainList->getTemp()->getValue()->getTemp() != nullptr && MainList->getTemp()->getValue()->getCurr()->getValue()->getName() != name
            && MainList->getTemp()->getValue()->getCurr()->getValue()->getAuthor() != author
            && MainList->getTemp()->getValue()->getCurr()->getValue()->getYear() != year
            && MainList->getTemp()->getValue()->getCurr()->getValue()->getSize() != size
            && MainList->getTemp()->getValue()->getCurr()->getValue()->getDescription() != description ){

            MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getCurr());
            MainList->getTemp()->getValue()->setCurr(MainList->getTemp()->getValue()->getCurr()->getNext());
        }
        if(MainList->getTemp()->getValue()->getCurr() == nullptr){
            delete delPtr;
            return true;
        }else{
            MainList->getTemp()->getValue()->getTemp()->setNext(MainList->getTemp()->getValue()->getCurr()->getNext());
            MainList->getTemp()->getValue()->getCurr()->setNext(nullptr);
            delPtr = MainList->getTemp()->getValue()->getCurr();
            delete delPtr;
            MainList->getTemp()->getValue()->substractSize();
            return this->deleteImage(json);
        }

    }


}

ptree DataBase::fillPtreeImage(NodeHuff<Image*> *image, vector<string> vec) {

    ptree ptim;
    for (int i = 0; i < vec.size(); i++) {
        string at = vec[i];
        if (at.compare("name") == 0) {
            ptim.put("name",image->getValue()->getName());
        } else if (at.compare("author") == 0) {
            ptim.put("author",image->getValue()->getAuthor());
        } else if (at.compare("year") == 0) {
            ptim.put("year",image->getValue()->getYear());
        } else if (at.compare("size") == 0) {
            ptim.put("size",image->getValue()->getSize());
        } else if (at.compare("description") == 0) {
            ptim.put("description",image->getValue()->getDescription());
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

        while (MainList->getTemp() != nullptr) {

            string newFolder = this->root + MainList->getTemp()->getValue()->getID();
            if (mkdir(newFolder.c_str(), 0777) == 0) {
                MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
                ptree allImages;
                int cont = 0;
                while(MainList->getTemp()->getValue()->getTemp() != nullptr){
                    ptree image;
                    image.put("name",MainList->getTemp()->getValue()->getTemp()->getValue()->getName());
                    image.put("author",MainList->getTemp()->getValue()->getTemp()->getValue()->getAuthor());
                    image.put("year",MainList->getTemp()->getValue()->getTemp()->getValue()->getYear());
                    image.put("size",MainList->getTemp()->getValue()->getTemp()->getValue()->getSize());
                    image.put("description",MainList->getTemp()->getValue()->getTemp()->getValue()->getDescription());
                    allImages.put("Image"+to_string(cont),jManager->ptreeToString(image));
                    cont++;
                    MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());
                }
                //Making a file
                ofstream file;
                file.open(root+MainList->getTemp()->getValue()->getID()+"/MetaData.txt");
                file << jManager->ptreeToString(allImages);
                file.close();
                folders.push_back(MainList->getTemp()->getValue()->getID());
            } else {
                MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
                ptree allImages;
                int cont = 0;
                while(MainList->getTemp()->getValue()->getTemp() != nullptr){
                    ptree image;
                    image.put("name",MainList->getTemp()->getValue()->getTemp()->getValue()->getName());
                    image.put("author",MainList->getTemp()->getValue()->getTemp()->getValue()->getAuthor());
                    image.put("year",MainList->getTemp()->getValue()->getTemp()->getValue()->getYear());
                    image.put("size",MainList->getTemp()->getValue()->getTemp()->getValue()->getSize());
                    image.put("description",MainList->getTemp()->getValue()->getTemp()->getValue()->getDescription());
                    allImages.put("Image"+to_string(cont),jManager->ptreeToString(image));
                    cont++;
                    MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());
                }
                //Making a file
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

    ofstream file;
    file.open("../Master/imagesID.txt");
    file << this->imageID;
    file.close();

}

void DataBase::loadInMemory() {

}

void DataBase::showDirs() {
    if(!MainList->isEmpty()){

        MainList->setTemp(MainList->getHead());
        cout<<"[";
        while(MainList->getTemp()->getNext() != nullptr){

            cout<<MainList->getTemp()->getValue()->getID()<<",";
            MainList->setTemp(MainList->getTemp()->getNext());
        }MainList->setTemp(MainList->getTemp());
        cout<<MainList->getTemp()->getValue()->getID()<<"]"<<endl;
    }else{
        cout<<"[]"<<endl;
    }

}

void DataBase::showALLImages(string galery) {

    MainList->setTemp(MainList->getHead());

    while(MainList->getTemp() != nullptr && MainList->getTemp()->getValue()->getID() != galery){
        MainList->setTemp(MainList->getTemp()->getNext());
    }
    if(MainList->getTemp() == nullptr){
        cout<<"No se encontró una galeria con el nombre <<"<<galery<<">>";

    }else{
        ptree imagesJson;

        MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getHead());
        int cont = 0;
        while(MainList->getTemp()->getValue()->getTemp() != nullptr){

            ptree ptim;
            ptim.put("name",MainList->getTemp()->getValue()->getTemp()->getValue()->getName());
            ptim.put("author",MainList->getTemp()->getValue()->getTemp()->getValue()->getAuthor());
            ptim.put("year",MainList->getTemp()->getValue()->getTemp()->getValue()->getYear());
            ptim.put("size",MainList->getTemp()->getValue()->getTemp()->getValue()->getSize());
            ptim.put("description",MainList->getTemp()->getValue()->getTemp()->getValue()->getDescription());

            imagesJson.put("Image"+to_string(cont),jManager->ptreeToString(ptim));
            cont++;

            MainList->getTemp()->getValue()->setTemp(MainList->getTemp()->getValue()->getTemp()->getNext());

        }
        this->jManager->printJson(imagesJson);
    }

}

void DataBase::compressData(string json , string galery) {

    vector<char> ch;
    for(int i=0;i<json.size();i++)
    {
        ch.push_back(json.at(i));
    }
    Compressor::Codified_File * code = this->compressor->compress(ch,"txt",this->root+galery+"/compress");
    this->compressor->writeToDiskComp(code);

}
//TODO: agregar a los archivos un identificador code + i tree + i para poder identificarlos en esta parte
// agregar tambien el numero de imagenes que hay para poder hacer unn for y descomprimir todas las imagenes

string DataBase::descompressData(string galery, string tree , string code) {
    Compressor::Codified_File * c = this->compressor->treeReconstructor(this->root+galery+"/"+tree+".txt",this->root+galery+"/"+code+".txt");
    Compressor::Decodified_File * d = this->compressor->decompress(c);
    this->compressor->writeToDiskDecomp(d);

    ifstream inFile;
    //TODO: completar esta parte con el iterador de las imagenes
    inFile.open(this->root+galery);
    string json = "";
    string x;
    if(inFile.is_open()){
        while(inFile >> x){
            json = json +x;
        }
        inFile.close();
    }else{
        cout<<"Cant open the file!"<<endl;
    }
    return json;

}


