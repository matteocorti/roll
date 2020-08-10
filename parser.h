/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    COMMA = 258,                   /* COMMA  */
    DICE = 259,                    /* DICE  */
    DIV = 260,                     /* DIV  */
    FUDGE = 261,                   /* FUDGE  */
    HIGH = 262,                    /* HIGH  */
    LCURLY = 263,                  /* LCURLY  */
    LOW = 264,                     /* LOW  */
    LPAREN = 265,                  /* LPAREN  */
    MINUS = 266,                   /* MINUS  */
    PERCENT = 267,                 /* PERCENT  */
    PLUS = 268,                    /* PLUS  */
    RCURLY = 269,                  /* RCURLY  */
    RPAREN = 270,                  /* RPAREN  */
    TIMES = 271,                   /* TIMES  */
    LE = 272,                      /* LE  */
    LT = 273,                      /* LT  */
    GE = 274,                      /* GE  */
    GT = 275,                      /* GT  */
    NE = 276,                      /* NE  */
    NUMBER = 277                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define COMMA 258
#define DICE 259
#define DIV 260
#define FUDGE 261
#define HIGH 262
#define LCURLY 263
#define LOW 264
#define LPAREN 265
#define MINUS 266
#define PERCENT 267
#define PLUS 268
#define RCURLY 269
#define RPAREN 270
#define TIMES 271
#define LE 272
#define LT 273
#define GE 274
#define GT 275
#define NE 276
#define NUMBER 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

  struct ir_node * node;
  int              int_type;

#line 115 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
