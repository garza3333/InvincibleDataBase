//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_JMANAGER_H
#define MYDATABASE_JMANAGER_H


using namespace std;
class JManager {


public:
    ptree stringToPtree(string json);
    string ptreeToString(ptree pt);
    void printJson(ptree json);
};


#endif //MYDATABASE_JMANAGER_H
