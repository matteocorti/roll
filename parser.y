%{

  /* Copyright (c) 2005, 2006, 2007  Matteo Corti
   * This file is part of roll
   *
   * You may distribute this file under the terms the GNU General Public
   * License.  See the file COPYING for more information.
   */
  
#include <roll.h>
#include <stdio.h>
#include <math.h>
#define YYSTYPE int
  
  int  yylex (void);
  void yyerror (char const *);

  char * out_buf      = NULL; /**< output buffer                         */
  int    out_buf_pos  = 0;    /**< current position in the output buffer */  
  int    out_buf_size = 0;    /**< current size of the output buffer     */

  char buf[33]; /**< temporary buffer for sprintf results */
  
  /** Appends a string to the output buffer
   * @param string string to append
   */
  void append_to_output(char * string) {

    int string_len = strlen(string);

    if (out_buf_pos + string_len > out_buf_size) {
      out_buf_size = out_buf_pos + string_len;
    }
    
    /* (re)-allocate */
    out_buf = realloc(out_buf, out_buf_size);
    if (out_buf == NULL) {
      fprintf(stderr, "Error: out of memory\n");
      exit(EXIT_FAILURE);
    }
    
    strcat(out_buf, string);
    
  }
  
  int roll_dice(int sides) {
    if (sides != HUNDRED) {
      return roll(sides);
    } else {
      /* d100 -> d10*10+d10 */
      int  d1 = roll(10);
      int d10 = roll(10) % 10;
      if (d1 == 0 && d10 == 0) {
        return 100;
      } else if (d10 == 0) {
        return d1;
      } else {
        return d10*10 + d1;
      }
    }
  }
  
  int compare(const void * p1, const void * p2) {
    
    const int i1 = *((const int *)p1);
    const int i2 = *((const int *)p2);
    
    if (i1 > i2)
      return 1;
    else if (i1 < i2)
      return -1;
    else
      return 0;
  }
  
  %}

%token NUMBER DICE PLUS MINUS RPAREN LPAREN PERCENT TIMES DIV HIGH LOW COMMA

%start roll

%%

roll : list {
  printf("%s\n", out_buf);
}
;

set : LCURLY expression RCURLY {
  $$ = $2
}
| NUMBER X LCURLY expression RCURLY {
  for (int i=0; i < $1; i++) {
    
}
;

list : expression {
  sprintf(buf, "%i", $1);
  append_to_output(buf);
  
}
| list COMMA expression {
  sprintf(buf, ", %i", $3);
  append_to _output(buf);
}    
;

expression : term {
               $$ = $1;
             }
           | term PLUS term {
               $$ = $1 + $3;
             }
           | term MINUS term {
               $$ = $1 - $3;
             }
           ;

factor   :   NUMBER dice {
	       int res=0;
	       int i;
               for(i=0; i<$1; i++) {
                 res += roll_dice($2);
               }
               $$ = res;
             }
           | NUMBER dice HIGH NUMBER {

               int res = 0;

               if ($4 > $1) {
                 error("the number of kept dices must be lower than the actual dices");
               }

               int * results;
               if (!(results = malloc(sizeof(int)*$1))) {
                 error("Out of memory");
               }

	       int i;
               for(i=0; i<$1; i++) {
                 results[i] = roll_dice($2);
               }
               qsort(results, $1, sizeof(int), &compare);
               for(i=($1-$4); i<$1; i++) {
                 res += results[i];
               }
               $$ = res;
             }
           | NUMBER dice LOW NUMBER {

               int res = 0;

               if ($4 > $1) {
                 error("the number of kept dices must be lower than the actual dices");
               }

               int * results;
               if (!(results = malloc(sizeof(int)*$1))) {
                 error("Out of memory");
               }

	       int i;
               for(i=0; i<$1; i++) {
                 results[i] = roll_dice($2);
               }
               qsort(results, $1, sizeof(int), &compare);
               for(i=0; i<$4; i++) {
                 res += results[i];
               }
               $$ = res;
             }
           | dice {
               $$ = roll_dice($1);
             }
           ;


term     :   NUMBER {
               $$ = $1;
             }
           | factor {
               $$ = $1;
             }
           | factor TIMES NUMBER {
               $$ = $1 * $3;
             }
           | factor DIV NUMBER {
               $$ = (int) ceil((float)$1 / $3);
             }
           | NUMBER TIMES factor {
               $$ = $1 * $3;
             }
           | NUMBER DIV factor {
               $$ = (int) ceil((float)$1 / $3);
             }
           | LPAREN expression RPAREN {
               $$ = $2;
             }
           ;

dice       : DICE NUMBER {
	       $$ = $2;
             }
           | DICE {
               $$ = 6;
             }
           | DICE PERCENT {
               $$ = HUNDRED;
             }
           ;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
