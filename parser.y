%{
#include <roll.h>
#include <stdio.h>
#include <math.h>
#define YYSTYPE int

int  yylex (void);
void yyerror (char const *);

%}

%token NUMBER DICE PLUS MINUS RPAREN LPAREN PERCENT TIMES DIV

%start roll

%%

roll       : expression {
               if ($1 < 0) {
                 printf("0\n");
                 exit(EXIT_FAILURE);
	       }
               printf("%i\n", $1);
             }

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
                 if ($1 != HUNDRED) {
	           res += roll($2);
                 } else {
                   /* d100 -> d10*10+d10 */
                   int  d1 = roll(10);
                   int d10 = roll(10);
                   if (d1 == 0 && d10 == 0) {
                     $$ = 100;
                   } else {
                     $$ = d10*10 + d1;
                   }
                 }
               }
               $$ = res;
             }
           | dice {
               $$ = $1;
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


