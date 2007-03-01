%option  noyywrap

%{
#include "parser.h"
%} 

%%

[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\+        { return PLUS; }
\-        { return MINUS; }
d|D       { return DICE; }
"("       { return LPAREN; }
")"       { return RPAREN; }

.         { printf("Error: unknown symbol '%s'\n", yytext); exit(-2); }

%%