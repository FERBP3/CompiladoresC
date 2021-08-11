#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace C0{

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in)
   {
      loc = new C0::Parser::location_type();
   };
  
   //get rid of override virtual function warning
   using FlexLexer::yylex;

   virtual
   int yylex( C0::Parser::semantic_type * const lval, 
              C0::Parser::location_type *location );
   // YY_DECL defined in mc_lexer.l
   // Method body created by flex in mc_lexer.yy.cc


private:
   /* yyval ptr */
   C0::Parser::semantic_type *yylval = nullptr;
   /* location ptr */
   C0::Parser::location_type *loc    = nullptr;
};

}

#endif /* END __MCSCANNER_HPP__ */