%{
#include <roll.h>
#include <stdio.h>
#include <math.h>
#define YYSTYPE int

int  yylex (void);
void yyerror (char const *);

int roll_dice(int sides) {
  if (sides != HUNDRED) {
    return roll(sides);
  } else {
    /* d100 -> d10*10+d10 */
    int  d1 = roll(10);
    int d10 = roll(10);
    if (d1 == 0 && d10 == 0) {
      return 100;
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

%token NUMBER DICE PLUS MINUS RPAREN LPAREN PERCENT TIMES DIV KEEP

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
                 res += roll_dice($2);
               }
               $$ = res;
             }
           | NUMBER dice KEEP NUMBER {

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


