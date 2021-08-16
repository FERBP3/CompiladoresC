#ifndef TYPE_H
#define TYPE_H
#include <string>
#include "Table.h"

using namespace std;

namespace C0{
class Table;

class Type{
    private:
        //int id;
        string name;
        int numItems;
        int tamBytes;
        int baseType;
        // TODO(2) Agregar un miembro llamado base de tipo apuntador a Table
        C0::Table *base;

    public:
        Type();
        Type(string name, int baseType, int numItems, int tam);
        Type(string name, int bytes);
        ~Type();
        int getBaseType();
        int getNumItems();
        int getTamBytes();
        string getName();
        // TODO(3) Crear una función set y get para el nuevo dato miembro base
        C0::Table* getBase();
        void setBase(C0::Table* base);

        string toString();
};
}
#endif
