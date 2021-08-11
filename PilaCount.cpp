#include "PilaCount.h"

PilaCount::PilaCount(){
    
}

PilaCount::~PilaCount(){

}

void PilaCount::push(int i){
    pila.push(i);
}

int PilaCount::pop(){
    int i = pila.top();
    pila.pop();
    return i;
}

int PilaCount::top(){
    return pila.top();
}