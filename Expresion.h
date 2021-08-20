#ifndef EXPRESION_H
#define EXPRESION_H
#include <string>
using namespace std;

namespace C0{
class Expresion{
    private:
    string dir;
    int type;

    public:
    Expresion();
    Expresion(string dir, int type);
    ~Expresion();
    int getType();
    string getDir();
    void setDir(string dir);
    void setType(int type);
};
}
#endif
