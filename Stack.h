// TODO(1) Cambiar la constante PILA_H por TSTACK_H
#ifndef TSTACK_H
#define TSTACK_H
#include <stack>
#include "Table.h"
using namespace std;

namespace C0{
class Stack{
    private:
        C0::Table* global;
        stack<C0::Table*> pila;

    public:
        Stack();
        ~Stack();
        void push();
        Table* pop();
        Table* top();
        Table* getGlobal();
        int getSize();
};
}
#endif
