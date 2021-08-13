%{
#include <string>
#include <iostream>
using namespace std;
bool coment = false;

#include "Scanner.hpp"
#undef  YY_DECL
#define YY_DECL int C0::Scanner::yylex( C0::Parser::semantic_type * const lval, C0::Parser::location_type *location )

using token = C0::Parser::token;


#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="C0::Scanner"
%option c++
%option yylineno

cadena \"([\x20-\x21\x23-\xFE])*\"
%s COMENTARIO

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}
<INITIAL>{
[0-9]+      {
               yylval->build< std::string >( yytext );
               return( token::NUMERO );
            }

"if"        {
               return( token::IF );
            }

"else"      {
               return( token::ELSE );
            }


"while"     {
               return( token::WHILE );
            }


"print"     {
               return( token::PRINT );
            }

"int"       {
               return( token::INT );
            }

"void"      {
               return( token::VOID );
            }

"char"      {
                return( token::CHAR );
            }

"float"     {
                return( token::FLOAT );
            }

"double"    {
                return( token::DOUBLE );
            }


"break"     {
               return( token::BREAK );
            }

"struct"    {
               return( token::STRUCT );
            }

"for"       {
                return(token::FOR);
            }

"switch"    {
                return(token::SWITCH);
            }

"case"      {
                return(token::CASE);
            }

"default"   {
                return(token::DEFAULT);
            }

"func"      {
               return( token::FUNC );
            }

"return"    {
               return( token::RETURN );
            }

[a-zA-Z][a-zA-Z0-9_]*   {
               yylval->build< std::string >( yytext );
               return( token::ID );
            }

{cadena}    {
               yylval->build< std::string >( yytext );
               return( token::STRING );
            }
"("       {
               return( token::LPAR );
            }

")"       {
               return( token::RPAR );
            }

"{"       {
               return( token::LKEY );
            }

"}"       {
               return( token::RKEY );
            }

"["       {
               return( token::LCOR );
            }

"]"       {
               return( token::RCOR );
            }

";"       {
               return( token::PYC );
            }

","       {
               return( token::COMA );
            } 

"+"       {
               return( token::MAS );
            }

"-"       {
               return( token::MENOS );
            }

"*"       {
               return( token::MUL );
            }

"/"       {
               return( token::DIV );
            }

"%"       {
               return( token::MOD );
            }

">"       {
               return( token::GT );
            }

"<"       {
               return( token::LT );
            }

">="       {
               return( token::GTE );
            }

"<="       {
               return( token::LTE );
            }

"="       {
               return( token::ASIG );
            }

"=="       {
               return( token::EQUAL );
            }

"!="       {
               return( token::DISTINCT );
            }

"||"       {
               return( token::OR );
            }

"&&"        {
               return( token::AND );
            }

"!"         {
               return( token::NOT );
            }

"."         {
                return(token::DOT);
            }

":"         {
                return(token::TWOP);
            }

"/*"    {
            coment=true;
            BEGIN(COMENTARIO);
         }


\n          {
               /** Update line number **/
               loc->lines();
            }

[ \t\r]     {}

.           {
               cout<<"ERROR LÉXICO: "<<yytext << endl;
            }
}
<COMENTARIO>{
[*/]  {}
[^*/] {}
"*/"  {
         coment=false;
         BEGIN(INITIAL);
      }
}
%%
int yyFlexLexer::yywrap(){
   return 1;
}
