#include "Type.h"

C0::Type::Type(){

}

C0::Type::Type(string name, int baseType, int numItems){
    this->name = name;
    this->baseType =baseType;
    this->numItems = numItems;
}

C0::Type::Type(string name, int bytes){
    this->name = name;
    this->tamBytes = bytes;
}

C0::Type::~Type(){

}

int C0::Type::getBaseType(){
    return baseType;
}

int C0::Type::getNumItems(){
    return numItems;
}

int C0::Type::getTamBytes(){
    return 1;
}

string C0::Type::getName(){
    return name;
}

// TODO(4) Programar  la función  setBase que recibe a base:*Table
// TODO(5) Programar la función getBase que retorna a base