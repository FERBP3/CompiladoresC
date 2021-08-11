#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>
#include <vector>
using namespace std;

#include "Scanner.hpp"
#include "parser.tab.hh"
// TODO(26) Quitar Table.h
#include "Table.h"
// TODO(27) Incluir Stack.h
//#include "Stack.h"
#include "Expresion.h"
#include "Quad.h"
#include "PilaCount.h"

namespace C0{
class Driver{
public:
   Driver() = default;
   virtual ~Driver();   
   void parse( const string& filename );
   string file;
   bool trace_parsing;

   void init();
   //TODO(63) Definir el prototipo de una función que envuelva un push a tstack
   //TODO(64) Definir el prototpio de una función que retorne un Table* al hacer pop a tstack
   /*************************************************************************/
   /*     FUNCIONES QUE ENVUELVEN EL FUNCIONAMIENTO DE LA TABLA DE SÍMBOLOS */
   /*************************************************************************/
   bool isInSymbol(string id);
   void addSymbol(string id);
   void setDir(string id, int dir);
   int getDir(string id);
   void setType(string id, int type);
   int getType(string id);
   void setVar(string id, string var);
   string getVar(string id);
   /*************************************************************************/
   /*     FUNCIONES QUE ENVUELVEN EL FUNCIONAMIENTO DE LA TABLA DE TIPOS */
   /*************************************************************************/
   // TODO(32) Agregar el prototipo para la funcion que envuelve a getName de la tabla de tipos
   // TODO(33) Agregar el prototipo para la funcion que envuelve a getTam de la tabla de tipos
   // TODO(34) Agregar el prototipo para la funcion que envuelve a getTipoBase de la tabla de tipos
   // TODO(35) Agregar el prototipo para la funcion que envuelve a getNumImtes de la tabla de tipos
   // TODO(36) Agregar el prototipo para la funcion que envuelve a getBase de la tabla de tipos
   // TODO(37) Agregar el prototipo para la funcion que envuelve a setBase de la tabla de tipos
   // TODO(69)  Agregar el prototipo para una función que agregue un tipo nuevo struct recibe: "struct", Table *t

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
   void variable(string id);
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
   // TODO(28) Borrar la definición de Table
   C0::Table *table = nullptr;   
   // TODO(29) Añadir un nuevo miembro llamado tstack de tipo Stack
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
   // TODO(38) Crear una variable miembro llamada dirStack de tipo apuntador a PilaCount
   
};
}

#endif /* END __MCDRIVER_HPP__ */
