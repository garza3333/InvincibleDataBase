//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_IMAGE_H
#define MYDATABASE_IMAGE_H

#include <string.h>
#include <string>
using namespace std;
class Image {
private:
    std::string name , author , description , extension;
    int size , year ,ID;

public:
    Image();
    Image(string nam , string aut , int yea , int siz , string des ,int id , string exten);

    /**
     *
     * @return name of this image
     */
    string getName();
    /**
     *
     * @param name assign the name of the image
     */
    void setName(string name);
    /**
     *
     * @return author of this image
     */
    string getAuthor();
    /**
     *
     * @param author assign the author of this image
     */
    void setAuthor(string author);
    /**
     *
     * @return description of this image
     */
    string getDescription();
    /**
     *
     * @param description  assign the description of this image
     */
    void setDescription(string description);
    /**
     *
     * @return size of image
     */
    int getSize();
    /**
     *
     * @param size assign size of image
     */
    void setSize(int siz);
    /**
     *
     * @return year of creation
     */
    int getYear();
    /**
     *
     * @param year assign the year of creation
     */
    void setYear(int year);

    int getID();

    string getExten();

    void  setExtension(string exte);

};


#endif //MYDATABASE_IMAGE_H
