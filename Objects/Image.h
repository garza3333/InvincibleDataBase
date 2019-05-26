//
// Created by Daniel on 21/05/2019.
//

#ifndef MYDATABASE_IMAGE_H
#define MYDATABASE_IMAGE_H

#include <string>

class Image {
private:
    std::string name , author , description ;
    int size , year ;

public:

    /**
     *
     * @return name of this image
     */
    std::string getName();
    /**
     *
     * @param name assign the name of the image
     */
    void setName(std::string name);
    /**
     *
     * @return author of this image
     */
    std::string getAuthor();
    /**
     *
     * @param author assign the author of this image
     */
    void setAuthor(std::string author);
    /**
     *
     * @return description of this image
     */
    std::string getDescription();
    /**
     *
     * @param description  assign the description of this image
     */
    void setDescription(std::string description);
    /**
     *
     * @return size of image
     */
    int getSize();
    /**
     *
     * @param size assign size of image
     */
    void setSize(int size);
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

};


#endif //MYDATABASE_IMAGE_H
