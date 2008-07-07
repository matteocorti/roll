%{

  /* Copyright (c) 2005, 2006, 2007  Matteo Corti
   * This file is part of roll
   *
   * You may distribute this file under the terms the GNU General Public
   * License.  See the file COPYING for more information.
   */

#include <roll.h>
#include <stdio.h>

  int  yylex (void);
  void yyerror (char const *);

  extern int sum_flag;
  
%}

%union{
  struct ir_node * node;
  int              int_type;
}

%token COMMA
%token DICE
%token DIV
%token HIGH
%token LCURLY
%token LOW
%token LPAREN
%token MINUS
%token PERCENT
%token PLUS
%token RCURLY
%token RPAREN
%token TIMES
%token <int_type> NUMBER

%type <node> dice
%type <node> term
%type <node> factor
%type <node> expression
%type <node> expression_list
%type <int_type> top_level_expression
%type <int_type> top_level_expression_list

%start roll

%%

roll : top_level_expression_list {
    if (sum_flag == TRUE) {
      printf("sum: %i\n", $1);
    }  
}
;

top_level_expression_list : top_level_expression {
  $$ = $1;
}
| top_level_expression COMMA top_level_expression_list {
  $$ = $1 + $3;
}
;

top_level_expression : expression {
  $$ = roll_expression($1, TRUE);
}
| LCURLY expression_list RCURLY {
  $$ = roll_expression($2, TRUE);
}
| NUMBER LCURLY expression_list RCURLY {
  
  int repetitions = $1;
  int i;
  int res;
  int sum = 0;
  
  for (i = 0; i < repetitions; i++) {
    res = roll_expression($3, TRUE);
    if (sum_flag == TRUE) {
      printf("sum: %i\n", res);
      sum += res;
    }
  }

  $$ = res;
  
}
;

expression_list : expression {
  $$ = $1;
}
| expression COMMA expression_list {
  $1->next = $3;
  $$ = $1;
}
;

expression : term {
  $$ = $1;
}
| expression PLUS term {
  $$ = new_op(OP_PLUS, $1, $3);
}
| expression MINUS term {
  $$ = new_op(OP_MINUS, $1, $3);
}
;

factor   :   NUMBER dice {
  $2->left = new_number($1);
  $$ = $2;
}
| NUMBER dice HIGH NUMBER {

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $2->left = new_number($1);
  $$ = new_op(OP_HIGH, new_number($4), $2);

}
| NUMBER dice LOW NUMBER {

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $2->left = new_number($1);
  $$ = new_op(OP_LOW, new_number($4), $2);

}
| dice {
  $$ = $1;
}
;


term     :   NUMBER {
  $$ = new_number($1);
}
| factor {
  $$ = $1;
}
| factor TIMES NUMBER {
  $$ = new_op(OP_TIMES, $1, new_number($3));
}
| factor DIV NUMBER {
  $$ = new_op(OP_DIV, $1, new_number($3));
}
| NUMBER TIMES factor {
  $$ = new_op(OP_TIMES, new_number($1), $3);
}
| NUMBER DIV factor {
  $$ = new_op(OP_DIV, new_number($1), $3);
}
| LPAREN expression RPAREN {
  $$ = $2;
}
;

dice       : DICE NUMBER {

  $$ = new_dice(new_number($2));
}
| DICE {
  $$ = new_dice(new_number(6));
}
| DICE PERCENT {
  $$ = new_dice(new_number(HUNDRED));
}
;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


