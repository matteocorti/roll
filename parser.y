%{

  /* Copyright (c) 2005-2019  Matteo Corti <matteo@corti.li>
   * This file is part of roll
   *
   * You may distribute this file under the terms the GNU General Public
   * License.  See the file COPYING for more information.
   */

#include <roll.h>
#include <stdio.h>

#define YYDEBUG 1
  
  int positive_flag = FALSE;
  
  int  yylex (void);
  void yyerror (char const *);

  extern int sum_flag;

#ifdef DEBUG
  extern int debug_flag;
#endif
  
%}

%initial-action
{
#ifdef DEBUG
  if (debug_flag > 0) { 
    yydebug=1;
  }
#endif
  
};

%union{
  struct ir_node * node;
  int              int_type;
}

%token COMMA
%token DICE
%token DIV
%token FUDGE
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
%token X
%token LE
%token LT
%token GE
%token GT
%token NE
%token <int_type> NUMBER

%type <node> dice
%type <node> filtered_dice
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

#ifdef DEBUG  
  debug("top_level_expression_list : top_level_expression");
#endif
  
  if (! positive_flag || $1 > 0) {
    $$ = $1;
  } else {
    $$ = 0;
  }
  
}
| top_level_expression COMMA top_level_expression_list {
  $$ = $1 + $3;
}
;

top_level_expression : expression {

#ifdef DEBUG
  if (debug_flag > 0) {
    print_tree("tree", $1, 0);
  }
#endif

  $$ = roll_expression($1, TRUE);
}
| LCURLY expression_list RCURLY {

#ifdef DEBUG
  if (debug_flag > 0) {
    print_tree("tree", $2, 0);
  }
#endif

  $$ = roll_expression($2, TRUE);

 }
| NUMBER LCURLY expression_list RCURLY {
  
  int repetitions = $1;
  int i;
  int res;
  int sum = 0;

#ifdef DEBUG
  if (debug_flag > 0) {
    print_tree("tree", $3, 0);
  }
#endif
  
  for (i = 0; i < repetitions; i++) {
    res = roll_expression($3, TRUE);
    if (sum_flag == TRUE) {
      printf("sum: %i\n", res);
      sum += res;
    }

  }

  $$ = sum;
  
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

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] expression : term\n");
  }
#endif

  $$ = $1;

 }
| expression PLUS term {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] expression : expression PLUS term\n");
  }
#endif

  $$ = new_op(OP_PLUS, $1, $3);

 }
| expression MINUS term {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] expression : expression MINUS term\n");
  }
#endif
  
  $$ = new_op(OP_MINUS, $1, $3);
  
}
;

factor   :   NUMBER filtered_dice {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] factor: %i filtered_dice\n", $1);
  }
#endif
  
  $$ = new_op(OP_REP, new_number($1), $2);
  
}
| NUMBER filtered_dice HIGH NUMBER {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] factor: %i filtered_dice HIGH NUMBER\n", $1);
  }
#endif

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $$ = new_op(OP_HIGH, new_number($4), new_op(OP_REP, new_number($1), $2));

}
| NUMBER filtered_dice LOW NUMBER {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] factor: %i filtered_dice LOW NUMBER\n", $1);
  }
#endif

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $$ = new_op(OP_LOW, new_number($4), new_op(OP_REP, new_number($1), $2));

}
| NUMBER filtered_dice LOW X {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] factor: %i filtered_dice MINUS LOW\n", $1);
  }
#endif

  if ($1 <= 1) {
    error("the number of dices must be greater than 1");
  }

  $$ = new_op(OP_HIGH, new_number($1-1), new_op(OP_REP, new_number($1), $2));
  
}
| NUMBER filtered_dice HIGH X {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] [PARSE] factor: %i filtered_dice MINUS HIGH\n", $1);
  }
#endif

  if ($1 <= 1) {
    error("the number of dices must be greater than 1");
  }

  $$ = new_op(OP_LOW, new_number($1-1), new_op(OP_REP, new_number($1), $2));

}
| filtered_dice {

#ifdef DEBUG
  if (debug_flag > 0) {
    printf("[DBG] factor: filtered_dice\n");
  }
#endif

  $$ = $1;
  
}
| NUMBER {
 $$ = new_number($1);
}
;

term     : factor {
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

filtered_dice : dice {
  $$ = $1;
}
| dice GT NUMBER {
  $$ = new_op(OP_GT, $1, new_number($3));
  
}
| dice GE NUMBER {
  $$ = new_op(OP_GE, $1, new_number($3));
}
| dice LT NUMBER {
  $$ = new_op(OP_LT, $1, new_number($3));
}
| dice LE NUMBER {
  $$ = new_op(OP_LE, $1, new_number($3));
}
| dice NE NUMBER {
  $$ = new_op(OP_NE, $1, new_number($3));
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
| DICE FUDGE {
  $$ = new_dice(new_number(FUDGE_DICE));
 }
| DICE NUMBER X {
   $$ = new_op(OP_TIMES, new_dice(new_number($2)), new_dice(new_number($2)) );
 }
;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


