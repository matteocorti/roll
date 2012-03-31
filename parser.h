/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMA = 258,
     DICE = 259,
     DIV = 260,
     FUDGE = 261,
     HIGH = 262,
     LCURLY = 263,
     LOW = 264,
     LPAREN = 265,
     MINUS = 266,
     PERCENT = 267,
     PLUS = 268,
     RCURLY = 269,
     RPAREN = 270,
     TIMES = 271,
     LE = 272,
     LT = 273,
     GE = 274,
     GT = 275,
     NE = 276,
     NUMBER = 277
   };
#endif
/* Tokens.  */
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 23 "parser.y"

  struct ir_node * node;
  int              int_type;



/* Line 2068 of yacc.c  */
#line 101 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


