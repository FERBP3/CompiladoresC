#ifndef TABLA_H
#define TABLA_H
#include <vector>
using namespace std;
#include "Symbol.h"
#include "Type.h"

namespace C0{
class Type;

class Table{
    private:
        vector<C0::Symbol> symTab;
        vector<C0::Type> typeTab;

    public:
        Table();
        ~Table();

        //Funciones para la tabla de símbolos
        void addSymbol(string id);
        bool isInSymbol(string id);
        void setDir(string id, int dir);
        void setType(string id, int type);
        void setTypeVar(string id, string type);
        void setArgs(string id, vector<int> args);
        int getDir(string id);
        int getType(string id);
        string getTypeVar(string id);
        vector<int> getArgs(string id);
        //vector<C0::Symbol> getSymTab();

        //Funciones para la tabla de tipos
        // Este entero es el indice donde se agrego el último elemento
        int addType(string name);
        int addType(string name, int tam);
        int addType(string name, int tipoBase, int numItems);

        int addTypeStruct(string name, Table* t);
        string getName(int id);

        int getNumItems(int id);
        int getTam(int id);
        int getTipoBase(int id);
        Table* getBase(int id);
        string getClase(string name);
        void setBase(int id, Table* t);
        vector<C0::Type>* getTypes();
        vector<C0::Symbol>* getSyms();
        //toString
        string toString();

        int getFullTam();

};
}
#endif
