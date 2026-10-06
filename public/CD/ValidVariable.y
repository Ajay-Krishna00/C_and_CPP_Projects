%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
int valid = 1;
%}

%token LETTER DIGIT NL

%%

input:
    /* empty */
    | input line
    ;

line:
    var NL {
        if (valid) {
            printf(" -> Result: VALID variable / identifier\n\n");
        }
        valid = 1;
        printf("Enter a variable name to validate: ");
    }
    | error NL {
        yyerrok;
        valid = 1;
        printf("Enter a variable name to validate: ");
    }
    ;

var:
    LETTER rest
    ;

rest:
    rest LETTER
    | rest DIGIT
    | /* empty */
    ;

%%

void yyerror(const char *s) {
    printf(" -> Result: INVALID variable (Must start with a letter and contain only letters/digits)\n\n");
    valid = 0;
}

int main() {
    printf("======================================================\n");
    printf("      YACC: VALID VARIABLE / IDENTIFIER CHECKER       \n");
    printf("  (Starts with letter, followed by letters or digits) \n");
    printf("======================================================\n");
    printf("Enter a variable name to validate (Ctrl+C to quit): ");
    yyparse();
    return 0;
}
