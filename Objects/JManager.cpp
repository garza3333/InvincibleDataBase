//
// Created by Daniel on 21/05/2019.
//

#include <sstream>
#include <iostream>
#include "JManager.h"


ptree JManager::stringToPtree(string s)
{
    std::istringstream iss(s);
    ptree document;
    read_json(iss, document);
    return document;
}

string JManager::ptreeToString(ptree pt) {
    std::ostringstream oss;
    write_json(oss, pt);
    return oss.str();
}
void JManager::printJson(ptree const& pt) {
    ostringstream oss;
    write_json(oss, pt);
    cout<<oss.str()<<endl;
}
