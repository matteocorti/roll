%option noyywrap
%option yylineno

%{
/* Copyright (c) 2005, 2006, 2007  Matteo Corti
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
d|D         { return DICE;    }
h|H         { return HIGH;    }
l|L         { return LOW;     }
"("         { return LPAREN;  }
")"         { return RPAREN;  }
"{"         { return LCURLY;  }
"}"         { return RCURLY;  }
"%"         { return PERCENT; }
["*"x]      { return TIMES;   }
\/          { return DIV;     }
,           { return COMMA;   }
[[:blank:]] /* ignore spaces */
.           { printf("Error: unknown symbol '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
