#include "Quad.h"

C0::Quad::Quad(){

}

C0::Quad::Quad(string operador, string arg1, string arg2, string res)
{
    this->op = operador;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->res = res;
}

string C0::Quad::getOp()
{
    return op;
}

string C0::Quad::getArg1(){
    return arg1;
}

string C0::Quad::getArg2(){
    return arg2;
}

string C0::Quad::getRes()
{
    return res;
}

