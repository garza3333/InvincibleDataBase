//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_JMANAGER_H
#define MYDATABASE_JMANAGER_H


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using boost::property_tree::ptree;
using  namespace std;

class JManager {


public:
    ptree stringToPtree(string json);
    string ptreeToString(ptree pt);
    void printJson(ptree const& pt);
};


#endif //MYDATABASE_JMANAGER_H
