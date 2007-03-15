%option  noyywrap

%{
#include "parser.h"
%} 

%%

[0-9]+    { yylval = atoi(yytext); return NUMBER; }
\+        { return PLUS;    }
\-        { return MINUS;   }
d|D       { return DICE;    }
k|K       { return KEEP;    }
"("       { return LPAREN;  }
")"       { return RPAREN;  }
"%"       { return PERCENT; }
["*"x]    { return TIMES;   }
\/        { return DIV;     }

.         { printf("Error: unknown symbol '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
