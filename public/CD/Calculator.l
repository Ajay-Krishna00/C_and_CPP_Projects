%{
#include <stdlib.h>
#include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+(\.[0-9]+)?   { yylval.val = atof(yytext); return NUMBER; }
[ \t]               { /* ignore whitespace */ }
\n                  { return NL; }
"+"                 { return ADD; }
"-"                 { return SUB; }
"*"                 { return MUL; }
"/"                 { return DIV; }
"%"                 { return MOD; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
.                   { return yytext[0]; }

%%
