%{
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap

%%

"for"                   { return FOR; }
"int"|"float"|"char"    { return TYPE; }
[0-9]+                  { return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }

"++"                    { return INC; }
"--"                    { return DEC; }
"<="                    { return LE; }
">="                    { return GE; }
"=="                    { return EQ; }
"!="                    { return NE; }
"<"                     { return LT; }
">"                     { return GT; }
"="                     { return ASSIGN; }
"+="                    { return PLUS_ASSIGN; }
"-="                    { return MINUS_ASSIGN; }

"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MUL; }
"/"                     { return DIV; }

";"                     { return SEMI; }
","                     { return COMMA; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }

[ \t\r\n]               { /* ignore whitespace and newlines */ }
.                       { return yytext[0]; }

%%
