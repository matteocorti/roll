/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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
    DISCARD = 260,                 /* DISCARD  */
    DIV = 261,                     /* DIV  */
    FUDGE = 262,                   /* FUDGE  */
    HIGH = 263,                    /* HIGH  */
    LCURLY = 264,                  /* LCURLY  */
    LOW = 265,                     /* LOW  */
    LPAREN = 266,                  /* LPAREN  */
    MINUS = 267,                   /* MINUS  */
    PERCENT = 268,                 /* PERCENT  */
    PLUS = 269,                    /* PLUS  */
    RCURLY = 270,                  /* RCURLY  */
    RPAREN = 271,                  /* RPAREN  */
    TIMES = 272,                   /* TIMES  */
    LE = 273,                      /* LE  */
    LT = 274,                      /* LT  */
    GE = 275,                      /* GE  */
    GT = 276,                      /* GT  */
    NE = 277,                      /* NE  */
    NUMBER = 278                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define COMMA 258
#define DICE 259
#define DISCARD 260
#define DIV 261
#define FUDGE 262
#define HIGH 263
#define LCURLY 264
#define LOW 265
#define LPAREN 266
#define MINUS 267
#define PERCENT 268
#define PLUS 269
#define RCURLY 270
#define RPAREN 271
#define TIMES 272
#define LE 273
#define LT 274
#define GE 275
#define GT 276
#define NE 277
#define NUMBER 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

  struct ir_node * node;
  int              int_type;

#line 118 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
