%{
#include <roll.h>
#include <stdio.h>
#define YYSTYPE int

int  yylex (void);
void yyerror (char const *);

%}

%token NUMBER DICE PLUS MINUS RPAREN LPAREN PERCENT

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

term     :   NUMBER {
               $$ = $1;
             }
           | NUMBER dice {
	       int res=0;
	       int i;
               for(i=0; i<$1; i++) {
	         res += $2;
               }
               $$ = res;
             }
           | dice {
               $$ = $1;
             }
           | LPAREN expression RPAREN {
               $$ = $2;
             }
           ;

dice       : DICE NUMBER {
	       $$ = roll($2);
             }
           | DICE {
               $$ = roll(6);
             }
           | DICE PERCENT {
               int  d1 = roll(10);
               int d10 = roll(10);
               if (d1 == 0 && d10 == 0) {
                 $$ = 100;
               } else {
                 $$ = d10*10 + d1;
               }
             }
           ;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


