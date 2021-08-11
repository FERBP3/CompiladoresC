// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 30 "parser.yy"

#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "Driver.hpp"
// TODO(62) Definir una variable externa numType: int

#undef yylex
#define yylex scanner.yylex

#line 59 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy"
namespace C0 {
#line 152 "parser.tab.cc"

  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg, Driver  &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        value.move< int > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_type: // type
      case symbol_kind::S_base: // base
      case symbol_kind::S_arreglo: // arreglo
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_NUMERO: // NUMERO
      case symbol_kind::S_STRING: // STRING
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 76 "parser.yy"
    {
        driver.init();
    }
#line 722 "parser.tab.cc"
    break;

  case 8: // $@2: %empty
#line 100 "parser.yy"
    {
        /* driver.type = $1; */
        driver.current_type = yystack_[0].value.as < int > ();
        /* driver.setType() */
    }
#line 732 "parser.tab.cc"
    break;

  case 12: // var: ID
#line 118 "parser.yy"
    {
        driver.variable(yystack_[0].value.as < std::string > ());
    }
#line 740 "parser.tab.cc"
    break;

  case 13: // $@3: %empty
#line 126 "parser.yy"
    { /*$2*/
        /* driver.basico = $1; */
    }
#line 748 "parser.tab.cc"
    break;

  case 14: // type: base $@3 arreglo
#line 130 "parser.yy"
    { /* $4 */
        yylhs.value.as < int > () =  yystack_[0].value.as < int > ();
    }
#line 756 "parser.tab.cc"
    break;

  case 15: // base: INT
#line 138 "parser.yy"
    {
        yylhs.value.as < int > () = 1;
    }
#line 764 "parser.tab.cc"
    break;

  case 16: // base: VOID
#line 143 "parser.yy"
    {
        yylhs.value.as < int > ()= 0;
    }
#line 772 "parser.tab.cc"
    break;

  case 17: // arreglo: LCOR NUMERO RCOR arreglo
#line 150 "parser.yy"
    {
        // TODO(64) Agregar las acciones semánticas para ingresar un tipo array
    }
#line 780 "parser.tab.cc"
    break;

  case 18: // arreglo: %empty
#line 155 "parser.yy"
    {
        // TODO(65) Agregar las acciones semánticas para convertir gBase en el tipo de arreglo
    }
#line 788 "parser.tab.cc"
    break;

  case 19: // $@4: %empty
#line 163 "parser.yy"
               {
        // TODO(66) Agregar las acciones semánticas para push en tstack
    }
#line 796 "parser.tab.cc"
    break;

  case 20: // $@5: %empty
#line 166 "parser.yy"
    {
        // TODO(67) Agregar las acciones semánticas para recuperar la tabla de la cima
        // TODO(68) Agregar un tipo nuevo a la tabla de tipos de tipo struct
        // TODO(71) Hacer gType igual a lo que regres la tabla de tipos al insertar el struct
    }
#line 806 "parser.tab.cc"
    break;

  case 24: // def_mem: base ID PYC
#line 182 "parser.yy"
               {
        // TODO(72) Comprobar que el id no se ha declarado
        // TODO(73) En caso de que no exista agregarlo a la tabla de símbolos
    }
#line 815 "parser.tab.cc"
    break;

  case 27: // $@6: %empty
#line 198 "parser.yy"
    {
        // TODO(74) Hacer un push a tstack    
    }
#line 823 "parser.tab.cc"
    break;

  case 28: // function: FUNC base ID LPAR $@6 list_args RPAR LKEY local_decls bloqueSentencias RKEY
#line 202 "parser.yy"
    {
        // TODO(75) Hacer pop a tskack
        // TODO(76) Validar que el id no está en la tabla de símbolos
        // TODO](77) En caso de no estar agregarlo
        // TODO(78) Agregar que es tipo func, su tipo de retorno, y su lista de paramétros
        // Almacenada en list_args
    }
#line 835 "parser.tab.cc"
    break;

  case 29: // list_args: args
#line 213 "parser.yy"
    {
        // TOTOD(80) Hacer que list_args.lista =  args.lista
    }
#line 843 "parser.tab.cc"
    break;

  case 30: // list_args: %empty
#line 218 "parser.yy"
    {
        // TODO(81) Hacer list_args.lista = nullptr
    }
#line 851 "parser.tab.cc"
    break;

  case 31: // args: args COMA arg
#line 226 "parser.yy"
    {
        // TODO(82) Agregar arg.type a args1.lista
        // TODO(83) Hacer args.lista = args1.lista
    }
#line 860 "parser.tab.cc"
    break;

  case 32: // args: arg
#line 232 "parser.yy"
    {
        // TODO(84) Agregar arg.type a args.lista
    }
#line 868 "parser.tab.cc"
    break;

  case 33: // arg: base ID
#line 239 "parser.yy"
            {
        // TODO(85) validar que el id no se ha declarado
        // TODO(85) Hacer arg.type = base.type
    }
#line 877 "parser.tab.cc"
    break;

  case 37: // local_list: local_list COMA local
#line 260 "parser.yy"
    { 
        //TODO(87) Similar a list_var
    }
#line 885 "parser.tab.cc"
    break;

  case 39: // local: ID
#line 270 "parser.yy"
    {
        //TODO(88) Similar a var
    }
#line 893 "parser.tab.cc"
    break;

  case 54: // list_params: params
#line 319 "parser.yy"
          {
        // TODO(90) Similar a list_args-> args
    }
#line 901 "parser.tab.cc"
    break;

  case 55: // list_params: %empty
#line 323 "parser.yy"
          {
        // TODO(91) Similar a list_args-> epsilon
    }
#line 909 "parser.tab.cc"
    break;

  case 56: // params: params COMA param
#line 331 "parser.yy"
    {
        // TODO(92) Similar a args-> args, arg
    }
#line 917 "parser.tab.cc"
    break;

  case 57: // params: param
#line 336 "parser.yy"
    {
        // TODO(93) Similar a args-> arg
    }
#line 925 "parser.tab.cc"
    break;

  case 58: // param: expresion
#line 343 "parser.yy"
    {
        // TODO(94) param.type = expresion.type
    }
#line 933 "parser.tab.cc"
    break;


#line 937 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const short Parser::yypact_ninf_ = -131;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
    -131,    17,  -131,  -131,   180,    41,  -131,  -131,    -6,  -131,
    -131,  -131,  -131,  -131,    13,  -131,    18,  -131,    22,   -22,
    -131,    -8,    41,  -131,    69,  -131,    31,  -131,  -131,    34,
       8,  -131,  -131,    22,     5,    41,    26,  -131,  -131,  -131,
     -22,    56,    25,    91,  -131,  -131,    22,  -131,  -131,    63,
      41,    89,  -131,  -131,  -131,   142,    11,    92,    93,    95,
     111,     9,   143,  -131,   131,   153,  -131,  -131,  -131,  -131,
    -131,  -131,   133,  -131,  -131,  -131,     9,   154,     9,   125,
      -1,    -1,     1,  -131,   160,  -131,     9,    60,  -131,   105,
    -131,  -131,  -131,     9,    51,  -131,   126,   145,  -131,    83,
       9,    -1,    -1,   112,    30,    46,   127,   139,   175,     9,
    -131,   125,   144,  -131,     9,     9,     9,     9,     9,  -131,
     143,    88,  -131,   162,     9,   155,  -131,    72,    55,     9,
       9,     9,     9,     9,     9,    -1,    -1,   118,   118,   163,
     164,  -131,   150,  -131,     0,     0,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,    83,    83,    83,    83,    83,
      83,   174,  -131,   153,  -131,   158,  -131,  -131,  -131,  -131,
     183,   118,  -131,  -131,  -131
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,     0,     5,     1,     0,     0,    15,    16,     0,     4,
       6,     8,    13,     7,     3,    26,     0,    19,     0,    18,
      25,     0,     0,    12,     0,    11,     0,    14,    27,     0,
       0,    23,     9,     0,     0,    30,     0,    20,    22,    10,
      18,     0,     0,    29,    32,    24,     0,    17,    33,     0,
       0,     0,    35,    31,    21,    41,    90,     0,     0,     0,
       0,     0,     0,    34,     0,    40,    43,    51,    50,    44,
      45,    46,     0,    47,    48,    49,     0,     0,    55,    91,
       0,     0,     0,    95,    70,    65,     0,     0,    39,     0,
      38,    28,    42,     0,     0,    92,     0,    54,    57,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
      66,    68,     0,    52,     0,     0,     0,     0,     0,    36,
       0,     0,    72,     0,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,    64,    59,    60,    61,    62,    63,    37,
      89,    53,    56,    71,    82,    75,    76,    78,    77,    80,
      79,    73,    74,    41,    87,    85,    88,    94,    93,    69,
       0,     0,    83,    86,    84
  };

  const short
  Parser::yypgoto_[] =
  {
    -131,  -131,  -131,  -131,  -131,  -131,  -131,   156,   167,  -131,
    -131,    10,   161,  -131,  -131,  -131,  -131,   173,  -131,   190,
    -131,  -131,  -131,   157,  -131,  -131,  -131,    85,    43,  -131,
     -55,  -131,  -131,    99,  -131,    86,   -60,  -131,   128,   -74,
    -131,  -131,  -130,  -131,  -131,  -131,  -131,  -131,  -131
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     4,     9,    10,    18,    24,    25,    11,
      19,    29,    27,    13,    22,    46,    30,    31,    14,    15,
      35,    42,    43,    44,    55,    63,    89,    90,    64,    65,
     164,    67,    68,    96,    97,    98,   103,   110,    79,   104,
      69,   172,   165,    70,    71,    72,    73,    74,    75
  };

  const unsigned char
  Parser::yytable_[] =
  {
      66,    87,    84,    85,    84,    85,   106,   105,   166,    17,
      92,    26,    84,    85,    12,    16,    94,     3,    99,     6,
       7,    21,   107,     5,    37,    23,   112,   126,   128,    28,
     116,   117,   118,   121,   101,    34,   102,    36,    86,    40,
     125,   174,   127,    45,    76,    41,    86,    77,    78,    99,
     135,   136,     6,     7,   144,   145,   146,   147,   148,    48,
      41,   161,   162,    49,    99,    62,   135,   136,   137,   155,
     156,   157,   158,   159,   160,   135,   136,   113,    52,   114,
     115,   116,   117,   118,   138,   122,    32,    33,   114,   115,
     116,   117,   118,   154,   129,   130,   131,   132,   133,   134,
     114,   115,   116,   117,   118,   150,    54,    33,    66,    50,
     143,   114,   115,   116,   117,   118,   114,   115,   116,   117,
     118,    56,   119,   120,    57,    58,    59,    60,    83,    80,
      81,    61,    82,   163,   129,   130,   131,   132,   133,   134,
     114,   115,   116,   117,   118,    56,    88,    91,    57,    58,
      59,    60,    93,     6,     7,    61,    56,    95,   100,    57,
      58,    59,    60,   124,   123,   139,    61,   114,   115,   116,
     117,   118,   114,   115,   116,   117,   118,   140,   141,   151,
     167,   168,   143,   114,   115,   116,   117,   118,   169,   153,
       5,     6,     7,    76,     8,   136,   108,   109,   171,   173,
      39,    47,    51,    38,    20,   149,   170,    53,   142,     0,
     152,     0,   111
  };

  const short
  Parser::yycheck_[] =
  {
      55,    61,     3,     4,     3,     4,     5,    81,   138,    15,
      65,    33,     3,     4,     4,     5,    76,     0,    78,    11,
      12,     3,    82,    10,    16,     3,    86,   101,   102,    37,
      30,    31,    32,    93,    35,     4,    37,     3,    37,    34,
     100,   171,   102,    17,    33,    35,    37,    36,    37,   109,
      20,    21,    11,    12,   114,   115,   116,   117,   118,     3,
      50,   135,   136,    38,   124,    55,    20,    21,    38,   129,
     130,   131,   132,   133,   134,    20,    21,    17,    15,    28,
      29,    30,    31,    32,    38,    34,    17,    18,    28,    29,
      30,    31,    32,    38,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    17,    17,    18,   163,    18,
      38,    28,    29,    30,    31,    32,    28,    29,    30,    31,
      32,     3,    17,    18,     6,     7,     8,     9,    17,    37,
      37,    13,    37,    15,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     3,     3,    16,     6,     7,
       8,     9,    19,    11,    12,    13,     3,     3,    33,     6,
       7,     8,     9,    18,    38,    38,    13,    28,    29,    30,
      31,    32,    28,    29,    30,    31,    32,    38,     3,    17,
      17,    17,    38,    28,    29,    30,    31,    32,    38,    34,
      10,    11,    12,    33,    14,    21,    36,    37,    40,    16,
      33,    40,    46,    30,    14,   120,   163,    50,   109,    -1,
     124,    -1,    84
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    42,    43,     0,    44,    10,    11,    12,    14,    45,
      46,    50,    52,    54,    59,    60,    52,    15,    47,    51,
      60,     3,    55,     3,    48,    49,    33,    53,    37,    52,
      57,    58,    17,    18,     4,    61,     3,    16,    58,    49,
      34,    52,    62,    63,    64,    17,    56,    53,     3,    38,
      18,    48,    15,    64,    17,    65,     3,     6,     7,     8,
       9,    13,    52,    66,    69,    70,    71,    72,    73,    81,
      84,    85,    86,    87,    88,    89,    33,    36,    37,    79,
      37,    37,    37,    17,     3,     4,    37,    77,     3,    67,
      68,    16,    71,    19,    77,     3,    74,    75,    76,    77,
      33,    35,    37,    77,    80,    80,     5,    77,    36,    37,
      78,    79,    77,    17,    28,    29,    30,    31,    32,    17,
      18,    77,    34,    38,    18,    77,    80,    77,    80,    22,
      23,    24,    25,    26,    27,    20,    21,    38,    38,    38,
      38,     3,    74,    38,    77,    77,    77,    77,    77,    68,
      17,    17,    76,    34,    38,    77,    77,    77,    77,    77,
      77,    80,    80,    15,    71,    83,    83,    17,    17,    38,
      69,    40,    82,    16,    83
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    41,    43,    42,    44,    44,    45,    45,    47,    46,
      48,    48,    49,    51,    50,    52,    52,    53,    53,    55,
      56,    54,    57,    57,    58,    59,    59,    61,    60,    62,
      62,    63,    63,    64,    65,    65,    66,    67,    67,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    74,    74,    75,    75,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      78,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    82,    83,    83,    84,    85,
      86,    86,    86,    87,    88,    89
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     3,     2,     0,     1,     1,     0,     4,
       3,     1,     1,     0,     3,     1,     1,     4,     0,     0,
       0,     8,     2,     1,     3,     2,     1,     0,    11,     1,
       0,     3,     1,     2,     2,     0,     3,     3,     1,     1,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     5,     1,     0,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     1,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     6,     2,     0,     3,     1,     5,     4,
       1,     2,     3,     5,     5,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUMERO",
  "STRING", "IF", "WHILE", "PRINT", "BREAK", "FUNC", "INT", "VOID",
  "RETURN", "STRUCT", "LKEY", "RKEY", "PYC", "COMA", "ASIG", "OR", "AND",
  "EQUAL", "DISTINCT", "LT", "GT", "LTE", "GTE", "MAS", "MENOS", "MUL",
  "DIV", "MOD", "LCOR", "RCOR", "NOT", "DOT", "LPAR", "RPAR", "IFX",
  "ELSE", "$accept", "program", "$@1", "declarations", "declaration",
  "decl_var", "$@2", "list_var", "var", "type", "$@3", "base", "arreglo",
  "decl_struct", "$@4", "$@5", "body_struct", "def_mem", "functions",
  "function", "$@6", "list_args", "args", "arg", "local_decls",
  "local_decl", "local_list", "local", "bloqueSentencias", "sentencias",
  "sentencia", "sentReturn", "sentProc", "list_params", "params", "param",
  "expresion", "complemento", "array", "condicion", "sentIf", "sentElse",
  "bloqueOSentencia", "sentWhile", "sentAsig", "left_part", "sentPutw",
  "sentPuts", "sentBreak", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,    76,    76,    76,    85,    87,    92,    94,   100,    99,
     110,   112,   117,   126,   125,   137,   142,   149,   154,   163,
     166,   163,   175,   177,   182,   190,   192,   198,   197,   212,
     217,   225,   231,   239,   247,   249,   254,   259,   264,   269,
     277,   279,   284,   286,   291,   293,   295,   297,   299,   301,
     303,   305,   309,   314,   319,   323,   330,   335,   342,   350,
     352,   354,   356,   358,   360,   362,   364,   369,   371,   373,
     375,   380,   382,   387,   389,   391,   393,   395,   397,   399,
     401,   403,   405,   409,   417,   419,   424,   426,   431,   439,
     444,   446,   448,   453,   459,   464
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    // Last valid token kind.
    const int code_max = 295;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.yy"
} // C0
#line 1424 "parser.tab.cc"

#line 468 "parser.yy"


void C0::Parser::error( const location_type &l, const std::string &err_message )
{
    cerr << "Error: " << err_message << " at " << l << endl;
}
