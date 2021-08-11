#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <vector>
using namespace std;

namespace C0{
class Symbol{
    private:
        string id;
        int dir;
        int type;
        string typeVar;
        vector<int> args;

    public:
        Symbol();
        Symbol(string id);
        ~Symbol();
        void setDir(int dir);
        void setType(int type);
        void setTypeVar(string type);
        void setArgs(vector<int> args);

        string getId();
        int getDir();
        int getType();
        string getTypeVar();
        vector<int> getArgs();
        int getNumArgs();
};
}
#endif