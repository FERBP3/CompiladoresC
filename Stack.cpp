#include "Stack.h"

C0::Stack::Stack(){
    pila.push(global);
}

C0::Stack::~Stack(){

}

void C0::Stack::push(){
    //printf("push\n");
    pila.push(Table());
}

C0::Table C0::Stack::pop(){
    Table tab = pila.top();
    pila.pop();
    return tab;
}

C0::Table* C0::Stack::top(){
    return &pila.top();
}

C0::Table* C0::Stack::getGlobal(){
    return &global;
}

int C0::Stack::getSize(){
    return pila.size();
}
