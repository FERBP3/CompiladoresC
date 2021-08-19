#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
#include "Table.h"
using namespace std;

namespace C0{
class Structure{
    public:
        Structure();
        Structure(string clase);
        ~Structure();
        string clase;
        int type;
        Table* tabla;
        string base;
        int des;
};
}
#endif
