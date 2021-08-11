#ifndef CUADRUPLA_H
#define CUADRUPLA_H

#include <string>
using namespace std;

namespace C0{
class Quad{
    private:
        string op;
        string arg1;
        string arg2;
        string res;

    public:
        Quad();
        Quad(string op, string arg1, string arg2, string res);
        string getOp();
        string getArg1();
        string getArg2();
        string getRes();
        
};
}
#endif