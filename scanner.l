%option noyywrap
%option yylineno

%{
/* Copyright (c) 2005-2011  Matteo Corti
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

#include "parser.h"

%} 

%%

[0-9]+      { yylval.int_type = atoi(yytext); return NUMBER; }
\+          { return PLUS;    }
\-          { return MINUS;   }
["*"x]      { return TIMES;   }
\/          { return DIV;     }
d|D         { return DICE;    }
f|F         { return FUDGE;   }
h|H         { return HIGH;    }
l|L         { return LOW;     }
"("         { return LPAREN;  }
")"         { return RPAREN;  }
"{"         { return LCURLY;  }
"}"         { return RCURLY;  }
">"         { return GT; }
">="        { return GE; }
"<"         { return LT; }
"<="        { return LE; }
"!="        { return NE; }
"<>"        { return NE; }
"%"         { return PERCENT; }
,           { return COMMA;   }
[[:blank:]] /* ignore spaces */
.           { printf("Error: unknown symbol '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
