%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

digit   [0-9]
number  {digit}+(\.{digit}+)?

%%

{number}      {
                 yylval.fval = strtod(yytext, NULL);
                 return NUM;
              }

[ \t]         ;   /* skip spaces and tabs */

\n             { return EOL; }

"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }

"("            { return '('; }
")"            { return ')'; }

.              { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}