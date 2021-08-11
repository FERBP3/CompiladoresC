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
%token                  IF WHILE PRINT BREAK FUNC
%token                  INT VOID RETURN STRUCT
%token                  LKEY RKEY PYC COMA

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
%type<int> type base arreglo
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
    functions      
    ;

declarations
    : 
    declarations declaration
    | 
    %empty
    ;

declaration
    : 
    decl_var
    | 
    decl_struct        
    ;
    
decl_var
    : 
    type  
    {
        /* driver.type = $1; */
        driver.current_type = $1;
        /* driver.setType() */
    }  
    list_var PYC
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
    arreglo /*$3*/
    { /* $4 */
        $$ =  $3;
    }
    ;

base
    : 
    INT 
    {
        $$ = 1;
    }
    | 
    VOID
    {
        $$= 0;
    }
    ;

arreglo
    : LCOR NUMERO RCOR  arreglo
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
    ;

body_struct
    : 
    body_struct def_mem
    | 
    def_mem
    ;

def_mem
    : 
    base ID PYC{
        // TODO(72) Comprobar que el id no se ha declarado
        // TODO(73) En caso de que no exista agregarlo a la tabla de símbolos
    }
    ;

functions
    :
    functions function
    | 
    function
    ;

function
    : 
    FUNC base ID LPAR
    {
        // TODO(74) Hacer un push a tstack    
    }
    list_args RPAR LKEY local_decls bloqueSentencias RKEY
    {
        // TODO(75) Hacer pop a tskack
        // TODO(76) Validar que el id no está en la tabla de símbolos
        // TODO](77) En caso de no estar agregarlo
        // TODO(78) Agregar que es tipo func, su tipo de retorno, y su lista de paramétros
        // Almacenada en list_args
    }
    ;

list_args
    : args
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
    base ID {
        // TODO(85) validar que el id no se ha declarado
        // TODO(85) Hacer arg.type = base.type
    }
    ;

local_decls
    : 
    local_decls local_decl
    | 
    %empty
    ;

local_decl
    : 
    base local_list PYC    
    ;

local_list
    : 
    local_list  COMA local
    { 
        //TODO(87) Similar a list_var
    }
    | 
    local
    ;

local
    : 
    ID
    {
        //TODO(88) Similar a var
    }
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
    ;

sentReturn
    : RETURN expresion PYC
    ;

sentProc
    : 
    ID LPAR list_params RPAR PYC
    ;

list_params
    : 
    params{
        // TODO(90) Similar a list_args-> args
    }
    | 
    %empty{
        // TODO(91) Similar a list_args-> epsilon
    }
    ;

params
    : 
    params COMA param
    {
        // TODO(92) Similar a args-> args, arg
    }
    | 
    param
    {
        // TODO(93) Similar a args-> arg
    }
    ;

param
    : expresion
    {
        // TODO(94) param.type = expresion.type
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
    DOT ID
    |
    array
    |
    LPAR list_params RPAR
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

bloqueOSentencia
    : 
    LKEY bloqueSentencias RKEY
    | 
    sentencia
    ;

sentWhile
    : 
    WHILE LPAR
    condicion
    RPAR 
    bloqueOSentencia    
    ;

sentAsig
    : 
    left_part ASIG expresion PYC
    ;

left_part
    : 
    ID
    | 
    ID array
    | 
    ID DOT ID
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
    : BREAK    
    PYC
    ;

%%

void C0::Parser::error( const location_type &l, const std::string &err_message )
{
    cerr << "Error: " << err_message << " at " << l << endl;
}
