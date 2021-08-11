#ifndef TABLA_H
#define TABLA_H
#include <vector>
using namespace std;
#include "Symbol.h"
#include "Type.h"

namespace C0{
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
        vector<C0::Symbol> getSymTab();

        //Funciones para la tabla de tipos    
        // Se debe modificar la función addType para que devuelva un entero
        // Este entero es el indice donde se agrego el último elemento    
        void addType(string  name);
        // TODO(6) Sobrecargar addType para que reciba un nombre: string, tam:int
        // TODO(7) Sobrecargar addType para que reciba un nombre: string, numeroItems:int, tipoBase:int
        // TODO(8) Definir el prototipo de getName para tabla de tipos, recibe id:int
        // TODO(9) Definir el prototipo para getNumItems, recibe id:int
        // TODO(10) Definir el prototipo para getTam, recibe id:int
        // TODO(11) Definir el prototipo para getTipoBase, recibe id:int
        // TODO(12) Definir el prototipo para getBase, recibe id:int
        // TODO(13) Definir el prototipo para setBase, recibe id:int y t:*Table

        // TODO(14) Definir el prototipo para getTypes, retorna un apuntador a la tabla de tipos
        // TODO(15) Definir el prototipo para getSyms, retorna un pauntador a la tabla de súmb

};
}
#endif
