#ifndef TYPE_H
#define TYPE_H
#include <string>
using namespace std;

namespace C0{
class Type{
    private:
        int id;
        string name;
        int baseType;
        int numItems;
        int tamBytes;
        // TODO(2) Agregar un miembro llamado base de tipo apuntador a Table
    
    public:
        Type();
        Type(string name, int baseType, int numItems);
        Type(string name, int bytes);
        ~Type();
        int getBaseType();
        int getNumItems();
        int getTamBytes();
        string getName();
        // TODO(3) Crear una función set y get para el nuevo dato miembro base
};
}
#endif