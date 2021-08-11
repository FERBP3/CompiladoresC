#ifndef PILA_H
#define PILA_H
#include <stack>
using namespace std;

class PilaCount{
    private:        
        stack<int> pila;

    public:
        PilaCount();
        ~PilaCount();
        void push(int n);
        int pop();
        int top();        
};

#endif
