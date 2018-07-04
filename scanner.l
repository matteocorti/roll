%option noyywrap
%option yylineno

%{
/* Copyright (c) 2005-2018  Matteo Corti <matteo@corti.li>
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

#include <limits.h>
#include "parser.h"

%} 

%%

[0-9]+      {
    errno = 0;
    long number =  strtol( yytext, NULL, 10);
    if ( errno != 0 && errno != ERANGE && number == 0 ) {
        printf("Error: incorrect number %s\n", yytext);
        exit(EXIT_FAILURE);
    }
    // we only accept integers
    if ( number > INT_MAX ) {
        printf("Error: %s is too large\n", yytext );
        exit(EXIT_FAILURE);
    }
    yylval.int_type = (int)number;
    return NUMBER;
}
\+          { return PLUS;    }
\-          { return MINUS;   }
["*"x]      { return TIMES;   }
\/          { return DIV;     }

d|D         { return DICE;    }
w|W         { return DICE; /* German */ }
t|T         { return DICE; /* Swedish */ }

f|F         { return FUDGE;   }
h|H|k|K     { return HIGH;    }
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
