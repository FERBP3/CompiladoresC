#include "Table.h"
#include <iostream>
#include <cstring>

#include "Type.h"

using namespace std;

C0::Table::Table(){
    addType("void", 1);
    addType("int", 4);
}

C0::Table::~Table(){

}

void C0::Table::addSymbol(string id){
    symTab.push_back(Symbol(id));
}

int C0::Table::addType(string name){
    typeTab.push_back(Type(name, 4));
    return typeTab.size()-1;
}

bool C0::Table::isInSymbol(string id){
    //cout<<"buscando ...."<<id<<endl;
    for(Symbol s: symTab){
        //cout<<"comparando con"<<s.getId()<<endl;
        if(strcmp(s.getId().c_str(), id.c_str())==0){
            //cout<<"se encontro la variable "<<id<<endl;
            return true;
        }
    }
    return false;
}

void C0::Table::setDir(string id, int dir){
    for(unsigned int i = 0; i < symTab.size(); i++){
        if(symTab[i].getId() == id){
            symTab[i].setDir(dir);
            return;
        }
    }
}

void C0::Table::setType(string id, int type){
    for(unsigned int i= 0; i < symTab.size();i++){
        if(symTab[i].getId() == id){
            symTab[i].setType(type);
            //cout<<s.getDir()<<endl;
            return;
        }
    }
}

void C0::Table::setTypeVar(string id, string type){
    for(unsigned int i= 0; i < symTab.size();i++){
        if(symTab[i].getId() == id){
            symTab[i].setTypeVar(type);
            //cout<<s.getDir()<<endl;
            return;
        }
    }
}

void C0::Table::setArgs(string id, vector<int> args){
    for(unsigned int i= 0; i < symTab.size();i++){
        if(symTab[i].getId() == id){
            symTab[i].setArgs(args);
            //cout<<s.getDir()<<endl;
            return;
        }
    }
}

int C0::Table::getDir(string id){
    for(Symbol s: symTab){
        if(s.getId() == id){
            return s.getDir();
        }
    }
    return -1;
}

int C0::Table::getType(string id){
    for(Symbol s: symTab){
        if(s.getId() == id){
            return s.getType();
        }
    }
    return -1;
}

string C0::Table::getTypeVar(string id){
    for(Symbol s: symTab){
        if(s.getId() == id){            
            return s.getTypeVar();
        }
    }
    return "";
}

vector<int> C0::Table::getArgs(string id){
    for(Symbol s: symTab){
        if(s.getId() == id){
            return s.getArgs();
        }
    }
    vector<int> a;
    return a;
}

vector<C0::Symbol> C0::Table::getSymTab(){
    return symTab;
}

// TODO(16) Programar addType para que reciba un nombre: string, tam:int
int C0::Table::addType(string name, int tam){
    typeTab.push_back(Type(name, tam));
    return typeTab.size()-1;
}

// TODO(17) Programar addType para que reciba un nombre: string, numeroItems:int, tipoBase:int
int C0::Table::addType(string name, int tipoBase, int numItems){
    int tam = numItems * getTam(tipoBase);
    Type newType = Type(name, tipoBase, numItems, tam);
    typeTab.push_back(newType);
    return typeTab.size()-1;
}

// TODO(18) Programar getName para tabla de tipos, recibe id:int
string C0::Table::getName(int id){
    if (id < 0 || id >= typeTab.size()){
        return "";
    }
    return typeTab[id].getName();
}

// TODO(19) Programar getNumItems, recibe id:int
int C0::Table::getNumItems(int id){
    if (id < 0 || id >= typeTab.size()){
        return -1;
    }
    return typeTab[id].getNumItems();
}

// TODO(20) Programar getTam, recibe id:int
int C0::Table::getTam(int id){
    if (id < 0 || id >= typeTab.size()){
        return -1;
    }
    return typeTab[id].getTamBytes();
}

// TODO(21) Programar getTipoBase, recibe id:int
int C0::Table::getTipoBase(int id){
    if (id < 0 || id >= typeTab.size()){
        return -1;
    }
    return typeTab[id].getBaseType();
}

// TODO(22) Programar getBase, recibe id:int
C0::Table* C0::Table::getBase(int id){
    if (id < 0 || id >= typeTab.size()){
        return nullptr;
    }
    return typeTab[id].getBase();
}

// TODO(23) Programar setBase, recibe id:int y t:*Tabl
void C0::Table::setBase(int id, Table* t){
    if (id < 0 || id >= typeTab.size()){
        return;
    }
    typeTab[id].setBase(t);
}

// TODO(24) Programar getTypes, retorna un apuntador a la tabla de tipos
vector<C0::Type>* C0::Table::getTypes(){
    return &typeTab;
}

// TODO(25) Programar getSyms, retorna un pauntador a la tabla de súmb
vector<C0::Symbol>* C0::Table::getSyms(){
    return &symTab;
}

string C0::Table::toString(){
    string cadena = "SIMBOLOS: "+to_string(symTab.size())+"\n";
    cadena += "id dir type typeVar args\n";
    for (int i=0; i<symTab.size(); i++){
        cadena += symTab[i].toString();
    }
    cadena += "\nTIPOS: "+to_string(typeTab.size())+"\n";
    cadena += "name numItems tam baseType\n";
    for (int i=0; i<typeTab.size(); i++){
        cadena += "TYPE "+to_string(i)+": "+typeTab[i].toString();
    }
    cadena += "\n";

    return cadena;
}
