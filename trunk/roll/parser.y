%{
#include <roll.h>
#include <stdio.h>
#define YYSTYPE int

int  yylex (void);
void yyerror (char const *);

%}

%token NUMBER DICE PLUS MINUS RPAREN LPAREN

%start roll

%%

roll       : expression {
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

term     : NUMBER {
               $$ = $1;
             }
           | NUMBER DICE NUMBER {
	       int res=0;
	       int i;
               for(i=0; i<$1; i++) {
	         res += roll($3);
               }
               $$ = res;
             }
           | DICE NUMBER {
               $$ = roll($2);
             }
           | LPAREN expression RPAREN {
               $$ = $2;
             }
           ;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
}


