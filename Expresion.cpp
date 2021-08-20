#include "Expresion.h"

C0::Expresion::Expresion(){

}

C0::Expresion::Expresion(string dir, int type){
    this->dir = dir;
    this->type = type;
}

C0::Expresion::~Expresion(){

}

int C0::Expresion::getType(){
    return type;
}

string C0::Expresion::getDir(){
    return dir;
}

void C0::Expresion::setDir(string dir){
    this->dir = dir;
}

void C0::Expresion::setType(int type){
    this->type = type;
}



