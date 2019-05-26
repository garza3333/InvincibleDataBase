//
// Created by Daniel on 21/05/2019.
//

#include "Image.h"

 std::string Image::getName(){
    return this->name;
}

void Image::setName(std::string n){
    this->name = n;
}

std::string Image::getAuthor(){
    return this->author;
}

void Image::setAuthor(std::string a) {
    this->author = a;
}

std::string Image::getDescription(){
    return this->description;
}

void Image::setDescription(std::string des) {
    this->description= des;
}

int Image::getSize() {
    return this->size;
}

void Image::setSize(int size) {
    this->size = size;
}

int Image::getYear(){
    return this->year;
}

void Image::setYear(int y) {
    this->year = y;
}
