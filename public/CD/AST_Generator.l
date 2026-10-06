%{
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+                  { strcpy(yylval.str, yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { strcpy(yylval.str, yytext); return ID; }
[ \t]                   { /* ignore whitespace */ }
\n                      { return NL; }
"+"                     { return ADD; }
"-"                     { return SUB; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"="                     { return ASSIGN; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
.                       { return yytext[0]; }

%%
