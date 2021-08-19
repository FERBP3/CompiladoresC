%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {C0}
%define api.parser.class {Parser}

%code requires{

#include "Expresion.h"
#include "Structure.h"
#include "Array.h"
namespace C0 {
    class Driver;
    class Scanner;
}

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }


%code{
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "Driver.hpp"
// TODO(62) Definir una variable externa numType: int
//extern int numType;

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%locations
%token <std::string>    ID
%token <std::string>    NUMERO
%token <std::string>    STRING
%token                  IF WHILE SWITCH CASE DEFAULT FOR PRINT BREAK FUNC
%token                  INT VOID CHAR FLOAT DOUBLE RETURN STRUCT
%token                  LKEY RKEY PYC TWOP COMA

%left                   ASIG /*=*/
%left                   OR /*||*/
%left                   AND /*&&*/
%left                   EQUAL DISTINCT /*== !=*/
%left                   LT GT  LTE GTE /* < >*/
%left                   MAS MENOS /* + -*/
%left                   MUL DIV MOD/* * / */
%left                   LCOR RCOR
%left                   NOT
%left                   DOT
%nonassoc               LPAR RPAR /* ( ) */
%nonassoc               IFX
%nonassoc               ELSE

%start program
%type<int> type base comp_arreglo arg param type_param
%type<vector<int>> list_args list_params args params parte_array
%type<Expresion> expresion condicion complemento left_part
%type<Structure> comp_struct
%type<Array> array

%%
program
    :
    {
        driver.init();

    }
    declarations
    {
        printf("FIN programa\n");
        printf("Tabla global\n%s\n", driver.getTablaGlobalString().c_str());
        //printf("size pila: %d\n",driver.getSizeTable());
    }
    ;

declarations
    :
    declarations declaration
    |
    %empty
    ;

declaration
    :
    type
    {
        driver.gType = $1;
        //printf("type\n");
    }
    decl_fun_var
    |
    decl_struct
    ;

decl_fun_var
    :
    list_var PYC
    |
    decl_fun
    ;

list_var
    :
    list_var COMA var
    |
    var
    ;

var
    :
    ID
    {
        if(driver.isInSymbol($1) || driver.gBase == 0){
            printf("La variable '%s' ya fue declarada o no puede ser de tipo void\n", $1.c_str());
            //YYERROR;
        }else{
            driver.addSymbol($1);
            driver.setType($1, driver.gType);
            driver.setDir($1, driver.gDir);
            driver.setVar($1, "variable");
            driver.gDir+= driver.getTam(driver.gType);
        }
    }
    ;

type
    :
    base
    {
        driver.gBase = $1;
    }
    comp_arreglo
    {
        $$ = $3;
    }
    |
    STRUCT ID
    {
        //printf("struct id\n");
        if (driver.isInSymbol($2)){
            if (driver.getClaseTop($2) == "struct"){
                $$ = driver.getType($2);
            }else{
                printf("El ID no representa un estructura\n");
                //YYERROR;
            }
        }else if (driver.isInSymbolGlobal($2)){
            if (driver.getClaseGlobal($2) == "struct"){
                $$ = driver.getTypeGlobal($2);
            }else{
                printf("El ID no representa un estructura\n");
                //YYERROR;
            }
        }else{
            printf("El id no existe\n");
            //YYERROR;
        }
    }
    ;

base
    :
    VOID
    {
        $$ = 0;
    }
    |
    INT
    {
        $$ = 1;
    }
    |
    CHAR
    {
        $$ = 2;
    }
    |
    FLOAT
    {
        $$ = 3;
    }
    |
    DOUBLE
    {
        $$ = 4;
    }
    ;

comp_arreglo
    : LCOR NUMERO RCOR comp_arreglo
    {
        int num = stoi($2);
        if (num > 0){
            $$ = driver.addType("arreglo", num, $4);

        }else{
            printf("El indice debe ser mayor a cero\n");
            //YYERROR;
        }
    }
    |
    %empty
    {
       $$ = driver.gBase;
    }
    ;

decl_struct
    :
    STRUCT LKEY{
        driver.pushTstack();
        driver.dirStack->push(driver.gDir);
        driver.gDir = 0;
    } body_struct RKEY
    {
        driver.gDir = driver.dirStack->pop();
        Table* tabla = driver.popTstack();
        driver.gType = driver.addTypeStruct("struct", tabla);
    } list_var PYC
    |
    STRUCT ID
    {
        //printf("aqui");
        driver.pushTstack();
        driver.dirStack->push(driver.gDir);
        driver.gDir = 0;
    }
    LKEY body_struct RKEY
    {
        driver.gDir = driver.dirStack->pop();
        Table* tabla = driver.popTstack();
        driver.gType = driver.addTypeStruct("struct", tabla);
        //printf("Tabla global desde struct \n%s\n", driver.getTablaGlobalString().c_str());

        //vector<Type>* tipos = driver.getTablaGlobal()->getTypes();
        //printf("size de tipos: %lu\n", tipos->size());
        /*
        for (int i=0; i<tipos->size(); i++){
            printf("%s\n", tipos->at(i).toString().c_str());
        }
        Type t = tipos->at(driver.gType);
        printf("%s\ntabla:%s\n\n",t.toString().c_str(), t.getBase()->toString().c_str());
        */

        // aqui funciona bien la tabla
        //printf("Tabla STRUCT\n%s\n\n", tabla.toString().c_str());

        if (driver.isInSymbol($2)){
            printf("La variable ya fue declarada\n");
            //YYERROR;
        }else{
            driver.addSymbol($2);
            driver.setType($2, driver.gType);
            driver.setVar($2, "struct");
        }
    }
    list_var PYC
    ;

body_struct
    :
    body_struct decl_local
    |
    decl_local
    ;

decl_fun
    :
    ID LPAR
    {
        driver.pushTstack();
        driver.dirStack->push(driver.gDir);
        driver.typeStack->push(driver.gType);
        driver.gDir = 0;

        driver.gReturnList.clear();
    }
    list_params RPAR LKEY decl_locales bloqueSentencias RKEY
    {
        driver.gDir = driver.dirStack->pop();
        driver.popTstack();
        int current_type_fun = driver.typeStack->pop();

        if (driver.isInSymbol($1)){
            printf("El id de la funcion ya fue declarado\n");
            //YYERROR;
        }else{
            for(int i=0; i<driver.gReturnList.size(); i++){
                if (driver.gReturnList[i] != current_type_fun){
                    printf("La sentencia de retorno no devuelve el tipo correcto de dato\n");
                    //YYERROR;
                }
            }
            driver.addSymbol($1);
            driver.setType($1, current_type_fun);
            driver.setVar($1, "func");
            driver.setArgsFunc($1, $4);
            //TODO genCode
        }
    }
    ;

list_params
    :
    params
    {
        $$ = $1;
    }
    |
    %empty
    {
        $$.clear();
    }
    ;

params
    :
    params COMA param
    {
        $1.push_back($3);
        $$ = $1;
    }
    |
    param
    {
        $$.clear();
        $$.push_back($1);
    }
    ;

param
    :
    type_param ID
    {
        if (driver.isInSymbol($2)){
            printf("El id de la funcion ya fue declarado\n");
            //YYERROR;
        }else{
            driver.addSymbol($2);
            driver.setType($2, $1);
            driver.setVar($2, "param");
            driver.setDir($2, driver.gDir);
            driver.gDir+= driver.getTam($1);
        }
        $$ = $1;
    }
    ;

type_param
    :
    base
    {
        $$ = $1;
    }
    |
    base parte_array
    {
        int lastType = driver.addType("arreglo", $2[0], $1);
        for (int i=1; i<$2.size(); i++){
            lastType = driver.addType("arreglo", $2[i], lastType);
        }
        $$ = lastType;
    }
    |
    STRUCT ID
    {
        if (driver.isInSymbol($2)){

            if (driver.getClaseTop($2) == "struct"){
                $$ = driver.getType($2);
            }else{
                printf("El id no representa una estructura\n");
                //YYERROR;
            }

        }else if (driver.isInSymbolGlobal($2)){
            if (driver.getClaseGlobal($2) == "struct"){
                $$ = driver.getTypeGlobal($2);
            }else{
                printf("El id no representa una estructura\n");
                //YYERROR;
            }
        }else{
            printf("El id no esta declarado\n");
            //YYERROR;
        }
    }
    ;

parte_array
    :
    LCOR NUMERO RCOR parte_array
    {
        int num = stoi($2);
        $4.push_back(num);
        $$ = $4;
    }
    |
    LCOR RCOR parte_array
    {
        $3.push_back(-1);
        $$ = $3;
    }
    |
    %empty
    ;

decl_locales
    :
    decl_locales decl_local
    |
    %empty
    ;

decl_local
    :
    decl_var
    |
    decl_struct
    ;

decl_var
    :
    type
    {
        driver.gType = $1;
    }
    list_var PYC
    ;

bloqueSentencias
    :
    sentencias
    |
    %empty
    ;

sentencias
    :
    sentencias sentencia
    |
    sentencia
    ;

sentencia
    :
    sentProc
    |
    sentIf
    |
    sentWhile
    |
    sentAsig
    |
    sentPutw
    |
    sentPuts
    |
    sentBreak
    |
    sentReturn
    |
    sentFor
    |
    sentSwitch
    ;

sentReturn
    :
    RETURN expresion PYC
    {
        driver.gReturnList.push_back($2.getType());
        //TODO genCode
    }
    |
    RETURN PYC
    {
        driver.gReturnList.push_back(0);
    }
    ;

sentProc
    :
    ID LPAR list_args RPAR PYC
    {
        string typeVar = driver.getTypeVarGlobal($1);
        if (driver.isInSymbolGlobal($1) && typeVar == "func"){
            vector<int> args = driver.getArgsGlobal($1);
            if (args.size() != $3.size()){
                printf("El numero de argumentos no coincide\n");
                //YYERROR;
            }else{
                for (int i=0; i<args.size(); i++){
                    if (args[i] != $3[i]){
                        printf("El tipo de argumentos no coincide\n");
                        //YYERROR;
                    }
                }
                //TODO genCode
            }
        }else{
            printf("El id no existe o no hace referencia a una función\n");
            //YYERROR;
        }
    }
    ;

list_args
    :
    args
    {
        $$ = $1;
    }
    |
    %empty
    ;

args
    :
    args COMA arg
    {
        $1.push_back($3);
        $$ = $1;
    }
    |
    arg
    {
        $$.clear();
        $$.push_back($1);
    }
    ;

arg
    :
    expresion 
    {
        $$ = $1.getType();
    }
    ;

expresion
    :
    expresion MAS expresion 
    |
    expresion MENOS expresion
    |
    expresion MUL expresion
    |
    expresion DIV expresion
    |
    expresion MOD expresion
    |
    LPAR expresion RPAR
    |
    NUMERO
    {
        // Por ahora solo es entero
        $$ = Expresion($1, 1);
    }
    |
    ID
    {
        //printf("agregando id global: %s\n", $1.c_str());
        driver.globalId.push($1);
    }
    complemento
    {
        $$ = Expresion($3.getDir(), $3.getType());
    }
    ;

complemento
    :
    comp_struct
    {
        string gId = driver.globalId.top();
        driver.globalId.pop();

        if ($1.base == gId){
            $$ = Expresion(gId, $1.type);
        }else{
            $$ = Expresion(gId+"["+to_string($1.des)+"]", $1.type);
        }

    }
    |
    array
    {
        string gId = driver.globalId.top();
        // checar si se hace pop()
        driver.globalId.pop();
        $$ = Expresion($1.dir+"["+gId+"]", $1.type);
    }
    |
    LPAR list_args RPAR
    {
        /* Casi igual a sentProc */
        string gId = driver.globalId.top();
        driver.globalId.pop();
        //printf("pop id global: %s\n", gId.c_str());

        string typeVar = driver.getTypeVarGlobal(gId);
        if (driver.isInSymbolGlobal(gId) && typeVar == "func"){
            vector<int> args = driver.getArgsGlobal(gId);
            if (args.size() != $2.size()){
                printf("El numero de argumentos no coincide\n");
                //YYERROR;
            }else{
                for (int i=0; i<args.size(); i++){
                    if (args[i] != $2[i]){
                        printf("El tipo de argumentos no coincide\n");
                        //YYERROR;
                        break;
                    }
                }
                // TODO nuevaTemporal ?
                $$ = Expresion(gId, driver.getTypeGlobal(gId));
                //TODO genCode
            }
        }else{
            printf("El id %s no existe o no hace referencia a una función\n", gId.c_str());
            //YYERROR;
        }
    }
    |
    %empty
    {
        string gId = driver.globalId.top();
        driver.globalId.pop();
        //printf("pop id global: %s\n", gId.c_str());

        if (driver.isInSymbol(gId)){

            $$ = Expresion(gId, driver.getType(gId));
            //printf("id: %s type:%d\n", $$.getDir().c_str(), $$.getType());
        }else if (driver.isInSymbolGlobal(gId)){
            $$ = Expresion(gId, driver.getTypeGlobal(gId));

        }else{
            printf("El id de retorno '%s' no está declarado\n", gId.c_str());
            //YYERROR;
        }
    }
    ;

array
    :
    array LCOR expresion RCOR
    {
        string clase = driver.getNameTop($1.type);
        //printf("name : %s\n", clase.c_str());
        if (clase == "arreglo"){
            if ($3.getType() == 1){
                $$.dir = "";
                $$.type = driver.getTipoBase($1.type);
                $$.tam = driver.getTam($$.type);
                //TODO genCode
            }else{
                printf("El índice para un arreglo debe ser entero\n");
                //YYERROR;
            }
        }else if(driver.getNameGlobal($1.type) == "arreglo"){
            if ($3.getType() == 1){
                $$.dir = "";
                $$.type = driver.getTipoBaseGlobal($1.type);
                $$.tam = driver.getTamGlobal($$.type);
                //TODO genCode
            }else{
                printf("El índice para un arreglo debe ser entero\n");
                //YYERROR;
            }

        }else{
            printf("El arrelo no tiene más dimensiones\n");
            //YYERROR;
        }
    }
    |
    LCOR expresion RCOR
    {
        string gId = driver.globalId.top();
        if (driver.isInSymbol(gId)){
            if (driver.getClaseTop(gId) == "arreglo"){
                if ($2.getType() == 1){
                    $$ = Array();
                    $$.dir = "";
                    $$.type = driver.getTipoBase(driver.getType(gId));
                    $$.tam = driver.getTam($$.type);
                    //TODO genCode

                }else{
                    printf("El índice debe ser entero\n");
                    //YYERROR;
                }
            }else{
                printf("El id %s no es un arreglo\n", gId.c_str());
                //YYERROR;
            }
        }else if(driver.isInSymbolGlobal(gId)){
            if (driver.getClaseGlobal(gId) == "arreglo"){
                if ($2.getType() == 1){
                    $$ = Array();
                    $$.dir = "";
                    $$.type = driver.getTipoBaseGlobal(driver.getTypeGlobal(gId));
                    $$.tam = driver.getTamGlobal($$.type);
                    //TODO genCode
                }else{
                    printf("El índice debe ser entero\n");
                    //YYERROR;
                }
            }else{
                printf("El id %s no es un arreglo\n", gId.c_str());
                //YYERROR;
            }

        }else{
             printf("El id %s no está declarado\n", gId.c_str());
            //YYERROR;
        }
    }
    ;

/* S-> S...S | ... | S...S| otro */
condicion
    :
    condicion OR condicion
    |
    condicion AND condicion
    |
    expresion EQUAL expresion
    |
    expresion DISTINCT expresion
    |
    expresion GT expresion
    |
    expresion LT expresion
    |
    expresion GTE expresion
    |
    expresion LTE expresion
    |
    NOT condicion
    |
    LPAR condicion RPAR
    ;

sentIf
    : IF LPAR
    condicion
    RPAR bloqueOSentencia
    sentElse
    ;

sentElse
    :
    ELSE bloqueOSentencia
    |
    %empty %prec IFX
    ;

sentWhile
    :
    WHILE LPAR
    condicion
    RPAR
    bloqueOSentencia
    ;

sentSwitch
    :
    SWITCH
    {
    //printf("switch token \n");
    }

    LPAR expresion
    {
    //printf("switch expresion \n");
    }

    RPAR LKEY body_switch
    RKEY
    {
    //printf("switch body \n");
    }
    ;

body_switch
    :
    caso body_switch
    |
    predeterminado
    |
    %empty
    ;

caso
    :
    CASE expresion TWOP sentencias
    ;

predeterminado
    :
    DEFAULT TWOP sentencias
    ;

sentFor
    :
    FOR
    {
    //printf("finish for token\n");
    }
    LPAR sentAsig
    {
    //printf("finish sentAsig\n");
    }

    {
    //printf("finish pyc for\n");
    }

    condicion
    {
    //printf("finish condicion\n");
    }

    PYC expresion
    {
    //printf("finish expresion \n");
    }

    RPAR
    {
    //printf("finish ) for \n");
    }

    bloqueOSentencia
    {
    //printf("finish bloqueOSentencia\n");
    }
    ;

sentAsig
    :
    left_part ASIG expresion PYC
    {
        //TODO genCode
    }
    ;


left_part
    :
    ID
    {
        driver.globalId.push($1);
    }
    comp_struct
    {
        string gId = driver.globalId.top();
        driver.globalId.pop();

        if ($3.base == gId){
            $$ = Expresion(gId, $3.type);
        }else{
            $$ = Expresion(gId+"["+to_string($3.des)+"]", $3.type);
        }
    }
    |
    ID
    {
        driver.globalId.push($1);
    }
    array
    {
        string gId = driver.globalId.top();
        driver.globalId.pop();

        $$ = Expresion(gId+"["+$3.dir+"]", $3.type);
    }
    ;

comp_struct
    :
    comp_struct DOT ID
    {
        if ($1.clase == "struct"){
            if ($1.tabla->isInSymbol($3)){
                $$.des = $1.des + $1.tabla->getDir($3);
                $$.clase = $1.tabla->getClase($3);
                $$.type = $1.tabla->getType($3);
                $$.tabla = $1.tabla->getBase($$.type);
                $$.base = $3;
            }else{
            printf("El id: '%s' no es un miembro de la estructura %s\n", $3.c_str(), $1.base.c_str());
            //printf("Tabla STRUCT\n%s\n\n", $1.tabla->toString().c_str());
            //YYERROR;
            }
        }else{
            printf("El comp_struct1.base: '%s' no es una estructura\n", $1.base.c_str());
            //YYERROR;
        }
    }
    |
    %empty
    {
        string gId = driver.globalId.top();

        if (driver.isInSymbol(gId)){
            $$.clase = driver.getClaseTop(gId);
            $$.type = driver.getType(gId);
            $$.tabla = driver.getBase($$.type);
            $$.base = gId;
            $$.des = 0;

            //printf("id encontrado en tope: %s\n", gId.c_str());

        }else if (driver.isInSymbolGlobal(gId)){
            $$.clase = driver.getClaseGlobal(gId);
            $$.type = driver.getTypeGlobal(gId);
            $$.tabla = driver.getBaseGlobal($$.type);
            $$.base = gId;
            $$.des = 0;

            //printf("id encontrado en global: %s type: %d\n", gId.c_str(), $$.type);
            //printf("Tabla STRUCT\n%s\n\n", $$.tabla->toString().c_str());
        }else{
            printf("El id '%s' no fue declarado\n", gId.c_str());
            //YYERROR;
        }
    }
    ;

sentPutw
    :
    PRINT LPAR expresion
    RPAR PYC
    ;

sentPuts
    :
    PRINT LPAR STRING
    RPAR PYC
    ;

sentBreak
    : BREAK PYC
    ;

bloqueOSentencia
    :
    LKEY bloqueSentencias RKEY
    |
    sentencia
    ;


%%

void C0::Parser::error( const location_type &l, const std::string &err_message )
{
    cerr << "Error: " << err_message << " at " << l << endl;
}
