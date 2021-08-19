#ifndef TYPE_H
#define TYPE_H
#include <string>
#include "Table.h"

using namespace std;

namespace C0{
class Table;

class Type{
    private:
        string name;
        int numItems;
        int tamBytes;
        int baseType;
        C0::Table *base;

    public:
        Type();
        Type(string name, int tipoBase, int numItems, int tam);
        Type(string name, int baseType, int numItems);
        Type(string name, int bytes);

        ~Type();
        int getBaseType();
        int getNumItems();
        int getTamBytes();
        string getName();
        C0::Table* getBase();
        void setBase(C0::Table* base);
        string toString();

};
}
#endif
