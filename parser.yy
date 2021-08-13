%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {C0}
%define parser_class_name {Parser}

%code requires{

// TODO(60) Incluir a Numero.h
// TODO(61) Incluir a Expresion.h
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
%type<int> type base array
//TODO (79) definir el no terminal list_args y args como vector<int>*
//TODO (89) definir el no terminal list_param y params como vector<int>*
//TODO(95) definir el no terminarl param como int
%%
program
    :
    {
        driver.init();
    }
    declarations
    /* functions */
    ;

declarations
    :
    declarations declaration
    |
    %empty
    ;

declaration
    :
    type decl_fun_var
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
    }
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
        driver.variable($1);
    }
    ;

type
    :
    base  /* $1 */
    { /*$2*/
        /* driver.basico = $1; */
    }
    comp_arreglo /*$3*/
    { /* $4 */
        /* $$ =  $3; */
    }
    |
    STRUCT ID
    ;

base
    :
    VOID
    {
        /* $$= 0; */
    }
    |
    INT
    {
        /* $$ = 1; */
    }
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
    }
    |
    %empty
    {
        // TODO(65) Agregar las acciones semánticas para convertir gBase en el tipo de arreglo
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
    ID LPAR list_params RPAR LKEY decl_locales bloqueSentencias RKEY
    {
        // TODO(74) Donde hacer un push a tskack **

        // TODO(75) Hacer pop a tskack
        // TODO(76) Validar que el id no está en la tabla de símbolos
        // TODO](77) En caso de no estar agregarlo
        // TODO(78) Agregar que es tipo func, su tipo de retorno, y su lista de paramétros
        // Almacenada en list_args
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
    |
    LCOR RCOR
    |
    %empty
    ;

decl_locales
    :
    decl_locales decl_local
    |
    %empty

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
    sentProc
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
    |
    ID complemento
    ;

complemento
    :
    comp_struct
    |
    array
    |
    LPAR list_params RPAR PYC
    |
    %empty
    ;

array
    :
    array LCOR expresion RCOR
    |
    LCOR expresion RCOR
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
    WHILE LPAR condicion RPAR LKEY body_switch RKEY
    ;

body_switch
    :
    caso body_switch
    |
    predeterminado
    |
    %empty

caso
    :
    CASE expresion PYC sentencias
    ;

predeterminado
    :
    DEFAULT TWOP sentencias
    ;

sentFor
    :
    FOR LPAR sentAsig PYC condicion PYC expresion RPAR bloqueOSentencia
    ;

sentAsig
    :
    left_part ASIG expresion PYC
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
    : BREAK
    PYC
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
