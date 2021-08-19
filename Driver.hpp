#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>
#include <vector>
using namespace std;

#include "Scanner.hpp"
#include "parser.tab.hh"
#include "Stack.h"
#include "Expresion.h"
#include "Quad.h"
#include "PilaCount.h"
#include "Structure.h"

namespace C0{
class Driver{
public:
   Driver() = default;
   virtual ~Driver();
   void parse( const string& filename );
   string file;
   bool trace_parsing;

   void init();

   // Funciones auxiliares
   int getSizeTable();
   string getTablaGlobalString();
   Table* getTablaGlobal();
   Table* getTablaTop();


   //TODO(63) Definir el prototipo de una función que envuelva un push a tstack
   void pushTstack();
   //TODO(64) Definir el prototpio de una función que retorne un Table* al hacer pop a tstack
   Table* popTstack();
   /*************************************************************************/
   /*     FUNCIONES QUE ENVUELVEN EL FUNCIONAMIENTO DE LA TABLA DE SÍMBOLOS */
   /*************************************************************************/
   bool isInSymbol(string id);
   bool isInSymbolGlobal(string id);

   void addSymbol(string id);
   void setDir(string id, int dir);
   int getDir(string id);
   void setType(string id, int type);
   int getType(string id);
   int getTypeGlobal(string id);
   string getTypeVarGlobal(string id);
   vector<int> getArgsGlobal(string id);

   void setVar(string id, string var);
   string getVar(string id);
   /*************************************************************************/
   /*     FUNCIONES QUE ENVUELVEN EL FUNCIONAMIENTO DE LA TABLA DE TIPOS */
   /*************************************************************************/
   int addType(string id, int numItems, int tipoBase);
   string getNameTop(int id);
   string getClaseTop(string name);
   string getClaseGlobal(string name);

   int getTam(int id);
   int getTipoBase(int id);
   int getNumItems(int id);
   Table* getBase(int id);
   Table* getBaseGlobal(int id);

   void setBase(int id, Table* base);
   int addTypeStruct(string name, Table* t);
   void setArgsFunc(string id, vector<int> args);

   /****************************************************/
   /*     FUNCIONES QUE REALIZAN EL ANÁLISIS SEMÁNTICO */
   /****************************************************/
   Expresion add(Expresion e1, Expresion e2);
   Expresion sub(Expresion e1, Expresion e2);
   Expresion mul(Expresion e1, Expresion e2);
   Expresion div(Expresion e1, Expresion e2);
   Expresion number(string num);
   Expresion ident(string id);
   Expresion _or(Expresion e1, Expresion e2);
   Expresion _and(Expresion e1, Expresion e2);
   Expresion gt(Expresion e1, Expresion e2);
   Expresion lt(Expresion e1, Expresion e2);
   Expresion equal(Expresion e1, Expresion e2);
   Expresion distinct(Expresion e1, Expresion e2);
   void asign(string id, Expresion e2); 
   void writew(Expresion e);
   void writes(string s, int c);
   bool variable(string id);
   /***********************************************/
   /*     FUNCIONES QUE GENERAN CÓDIGO INTERMEDIO */
   /***********************************************/ 
   void addQuad(Quad q)  ;
   void _if(Expresion e, int n);   
   void _while(Expresion e, int n);   
   void _goto(string label, int n);
   void _label(string label, int n);
   string newLabel(int n);
   string newTemp();
   void printCI();

   void printSymTab();
   /*******************************************/
   /*     FUNCIONES QUE GENERAN CÓDIGO OBJETO */
   /*******************************************/      
   void generateStrings();
   void translate();
   void addString(string s);

   
private:
   // TODO(28) Borrar la definición de Table C0::Table *table = nullptr;   
   // TODO(29) Añadir un nuevo miembro llamado tstack de tipo Stack
   C0::Stack tstack;
   void parse_helper( std::istream &stream );
   C0::Parser  *parser  = nullptr;
   C0::Scanner *scanner = nullptr;
   string output;
   string filename;

public:
   PilaCount *iStack;
   PilaCount *wStack;
   int numTemp;
   int numIf;
   int numString;
   int numWhile;
   int numWhile2 = 0;
   int gDir = 0;
   vector<Quad> ci;
   int current_type;
   vector<string> strings;
   // TODO(30) Agregar una variable entera llamada gType
   int gType;
   // TODO(31) Agregar una variable entera llamada gBase
   int gBase;
   // TODO(38) Crear una variable miembro llamada dirStack de tipo apuntador a PilaCount
   PilaCount* dirStack;
   PilaCount* typeStack;
   vector<int> gReturnList;
   stack<string> globalId;
   //string gId;
};
}

#endif /* END __MCDRIVER_HPP__ */
