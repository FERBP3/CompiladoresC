%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {C0}
%define api.parser.class {Parser}

%code requires{

// TODO(60) Incluir a Numero.h
// TODO(61) Incluir a Expresion.h
#include "Expresion.h"
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

%locations
%start program
%type<int> type base parte_array comp_arreglo
//TODO (79) definir el no terminal list_args y args como vector<int>*
%type<vector<int>*> list_args args
//TODO (89) definir el no terminal list_param y params como vector<int>*
%type<vector<int>*> list_params params
//TODO(95) definir el no terminal param como int
%type<int> arg param
%type<Expresion> expresion condicion

%%
program
    :
    {
        driver.init();
        //printf("%d\n",driver.getSizeTable());
    }
    declarations
    {
        printf("FIN programa\n");
        printf("Tabla global\n%s\n", driver.getTablaGlobal().c_str());
        printf("size pila: %d\n",driver.getSizeTable());

    }
    ;

declarations
    :
    declarations declaration
    {
        //printf("declarations\n");
    }
    |
    %empty
    ;

declaration
    :
    type
    {
        driver.gType = $1;
    }
    decl_fun_var
    {
    //printf("decl_fun_var\n");
    }
    |
    decl_struct
    ;

decl_fun_var
    :
    list_var PYC
    {
        /* driver.type = $1; */
        /* driver.current_type = $1; */
        /* driver.setType() */
        /* printf("list_var PYC\n"); */
    }
    |
    decl_fun
    ;

list_var
    :
    list_var
    { 
    // printf("list_var \n");
    }
    COMA
    {
    // printf("COMA \n");
    }
    var
    {
     //printf("var \n");
    }
    |
    var
    ;

var
    :
    ID
    {
        driver.variable($1);
    }
    ;

type
    :
    base  /* $1 */
    { /*$2*/
        driver.gBase = $1;
    }
    comp_arreglo /*$3*/
    { /* $4 */
        $$ = $3;
    }
    |
    STRUCT ID
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
    |
    FLOAT
    |
    DOUBLE
    ;

comp_arreglo
    : LCOR NUMERO RCOR comp_arreglo
    {
        // TODO(64) Agregar las acciones semánticas para ingresar un tipo array
        int num = stoi($2);
        //printf("tam arr: %d\n", num);
        //printf("comp_arreglo: %d\n", $4);
        if (num > 0){
            $$ = driver.addType("arreglo", num, $4);

        }else{
            printf("El indice debe ser mayor a cero\n");
        }
    }
    |
    %empty
    {
       // TODO(65) Agregar las acciones semánticas para convertir gBase en el tipo de arreglo
       $$ = driver.gBase;
    }
    ;

decl_struct
    :
    STRUCT LKEY{
        // TODO(66) Agregar las acciones semánticas para push en tstack
    } body_struct RKEY
    {
        // TODO(67) Agregar las acciones semánticas para recuperar la tabla de la cima
        // TODO(68) Agregar un tipo nuevo a la tabla de tipos de tipo struct
        // TODO(71) Hacer gType igual a lo que regres la tabla de tipos al insertar el struct
    } list_var PYC
    |
    STRUCT ID LKEY body_struct RKEY list_var PYC
    ;

body_struct
    :
    body_struct decl_local
    |
    decl_local
    ;

decl_fun
    :
    ID
    {
    //printf("ID FUNC: %s\n", $1.c_str());
    }

    LPAR list_params
    {
    //printf("finish list_params\n");
    }

    RPAR LKEY decl_locales
    {
    //printf("finish decl_locales\n");
    }

    bloqueSentencias
    {
    //printf("finish bloqueSentencias");
    }

    RKEY
    {
        // TODO(74) Donde hacer un push a tskack **

        // TODO(75) Hacer pop a tskack
        // TODO(76) Validar que el id no está en la tabla de símbolos
        // TODO](77) En caso de no estar agregarlo
        // TODO(78) Agregar que es tipo func, su tipo de retorno, y su lista de paramétros
        // Almacenada en list_args
        //printf("finish FUNC: %s\n", $1.c_str());
    }
    ;

list_params
    :
    params
    |
    %empty
    ;

params
    :
    params COMA param
    |
    param
    ;

param
    :
    type_param ID
    {
    //printf("finish type_param id\n");
    }
    ;

type_param
    :
    base parte_array
    |
    STRUCT ID
    ;

parte_array
    :
    parte_array LCOR NUMERO RCOR
    {
    //printf("corchetes y numero\n");
    }
    |
    LCOR RCOR
    {
    //printf("corchetes\n");
    }
    |
    %empty
    ;

decl_locales
    :
    decl_locales decl_local
    |
    %empty
    {
    //printf("finish decl_locales empty\n");
    }
    ;

decl_local
    :
    decl_var
    |
    decl_struct
    ;

decl_var
    :
    type list_var PYC

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
    |
    RETURN PYC
    ;

sentProc
    :
    ID LPAR list_args RPAR PYC
    ;

list_args
    :
    args
    {
        // TOTOD(80) Hacer que list_args.lista =  args.lista
    }
    | 
    %empty
    {
        // TODO(81) Hacer list_args.lista = nullptr
    }
    ;

args
    :
    args COMA arg
    {
        // TODO(82) Agregar arg.type a args1.lista
        // TODO(83) Hacer args.lista = args1.lista
    }
    |
    arg
    {
        // TODO(84) Agregar arg.type a args.lista
    }
    ;

arg
    :
    expresion {
        // TODO(85) validar que el id no se ha declarado
        // TODO(85) Hacer arg.type = base.type
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
    //printf("finish numero expresion %s\n", $1.c_str());
    }
    |
    ID
    {
    //printf("finish id expresion %s\n", $1.c_str());
    }
    complemento
    {
    //printf("finish complemento expresion\n");
    }
    ;

complemento
    :
    comp_struct
    |
    array
    |
    LPAR
    list_args
    RPAR
    {//printf("finish list_params complemento\n");
    }
    |
    %empty
    ;

array
    :
    array LCOR expresion RCOR
    {
    //printf("array \n");
    }
    |
    LCOR expresion RCOR
    {
    //printf("array \n");
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
    left_part
    {
    //printf("finish left part\n");
    }
    ASIG expresion PYC
    ;


left_part
    :
    ID comp_struct
    |
    ID array
    ;

comp_struct
    :
    comp_struct DOT ID
    |
    %empty
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
