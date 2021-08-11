#include "Symbol.h"

C0::Symbol::Symbol(){

}
        
C0::Symbol::Symbol(string id){
    this->id = id;
}

C0::Symbol::~Symbol(){

}


void C0::Symbol::setDir(int dir){
    this->dir = dir;
}

void C0::Symbol::setType(int type){
    this->type = type;
}

void C0::Symbol::setTypeVar(string type){
    typeVar = type;
}

void C0::Symbol::setArgs(vector<int> args){
    this->args = args;
}

string C0::Symbol::getId(){
    return id;
}

int C0::Symbol::getDir(){
    return dir;
}

int C0::Symbol::getType(){
    return type;
}

string C0::Symbol::getTypeVar(){
    return typeVar;
}

vector<int> C0::Symbol::getArgs(){
    return args;
}

int C0::Symbol::getNumArgs(){
    return args.size();
}