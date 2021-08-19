#include "Type.h"
#include "Table.h"

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

C0::Type::Type(string name, int tipoBase, int numItems, int tam){
    this->name = name;
    this->baseType = tipoBase;
    this->numItems = numItems;
    this->tamBytes = tam;
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
    return tamBytes;
}

string C0::Type::getName(){
    return name;
}

// TODO(4) Programar  la función  setBase que recibe a base:*Table
void C0::Type::setBase(C0::Table* base){
    this->base = base;
}

// TODO(5) Programar la función getBase que retorna a base
C0::Table* C0::Type::getBase(){
    return base;
}

string C0::Type::toString(){
    string cadena = "TYPE: "+name+" "+to_string(numItems)+" "+to_string(tamBytes)+" "+to_string(baseType)+"\n";
    return cadena;
}
