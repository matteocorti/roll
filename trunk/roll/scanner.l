%option  noyywrap

%{
#include "parser.h"
%} 

%%

[0-9]+    { yylval = atoi(yytext); return NUMBER; }
\+        { return PLUS;    }
\-        { return MINUS;   }
d|D       { return DICE;    }
h|H       { return HIGH;    }
l|L       { return LOW;     }
"("       { return LPAREN;  }
")"       { return RPAREN;  }
"%"       { return PERCENT; }
["*"x]    { return TIMES;   }
\/        { return DIV;     }

.         { printf("Error: unknown symbol '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
