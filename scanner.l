%option noyywrap
%option yylineno

%{
/* Copyright (c) 2005-2019  Matteo Corti <matteo@corti.li>
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

#ifdef DEBUG
    printf("[DBG] [SCAN] NUMBER = %i\n", yylval.int_type);
#endif

    return NUMBER;
}
\+          { return PLUS;    }

\-          {
#ifdef DEBUG
printf("[DBG] [SCAN] MINUS\n");
#endif
return MINUS;
}

["*"xX]     { return TIMES;   }
\/          { return DIV;     }

d|D|w|W|t|T {
#ifdef DEBUG
printf("[DBG] [SCAN] DICE\n");
#endif
return DICE;
}

f|F         { return FUDGE;   }
h|H|k|K     { return HIGH;    }
l|L         { return LOW;     }
x|X         { return DISCARD; }

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
