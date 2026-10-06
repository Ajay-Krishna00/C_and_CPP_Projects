%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);
%}

%union {
    double val;
}

%token <val> NUMBER
%token ADD SUB MUL DIV MOD LPAREN RPAREN NL
%type <val> expr term factor primary

%%

calc:
    /* empty */
    | calc line
    ;

line:
    NL
    | expr NL {
        printf(" -> Result = %.4g\n\n", $1);
        printf("Enter arithmetic expression (e.g., (12 + 4) * 3): ");
    }
    | error NL {
        yyerrok;
        printf("Enter arithmetic expression: ");
    }
    ;

expr:
    expr ADD term   { $$ = $1 + $3; }
    | expr SUB term  { $$ = $1 - $3; }
    | term           { $$ = $1; }
    ;

term:
    term MUL factor  { $$ = $1 * $3; }
    | term DIV factor {
        if ($3 == 0) {
            yyerror("Error: Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | term MOD factor {
        if ((int)$3 == 0) {
            yyerror("Error: Modulo by zero");
            $$ = 0;
        } else {
            $$ = (int)$1 % (int)$3;
        }
    }
    | factor         { $$ = $1; }
    ;

factor:
    ADD primary      { $$ = $2; }
    | SUB primary    { $$ = -$2; }
    | primary        { $$ = $1; }
    ;

primary:
    NUMBER           { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, " -> Parse Error: %s\n\n", s);
}

int main() {
    printf("======================================================\n");
    printf("           CALCULATOR USING LEX & YACC                \n");
    printf("     Supports: +, -, *, /, %%, unary +/-, ( )         \n");
    printf("======================================================\n");
    printf("Enter arithmetic expression (Ctrl+C to quit): ");
    yyparse();
    return 0;
}
