%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
int syntax_valid = 1;
%}

%token FOR TYPE NUMBER ID
%token INC DEC LE GE EQ NE LT GT ASSIGN PLUS_ASSIGN MINUS_ASSIGN
%token PLUS MINUS MUL DIV SEMI COMMA LPAREN RPAREN LBRACE RBRACE

%%

program:
    for_statement {
        if (syntax_valid) {
            printf("\n>>> RESULT: Valid C 'for' loop syntax!\n\n");
        }
    }
    ;

for_statement:
    FOR LPAREN init_expr SEMI cond_expr SEMI update_expr RPAREN body
    ;

init_expr:
    /* empty */
    | TYPE ID ASSIGN expr
    | ID ASSIGN expr
    | expr
    ;

cond_expr:
    /* empty */
    | expr rel_op expr
    | expr
    ;

rel_op:
    LT | GT | LE | GE | EQ | NE
    ;

update_expr:
    /* empty */
    | ID INC
    | INC ID
    | ID DEC
    | DEC ID
    | ID ASSIGN expr
    | ID PLUS_ASSIGN expr
    | ID MINUS_ASSIGN expr
    ;

body:
    SEMI
    | statement
    | LBRACE statement_list RBRACE
    ;

statement_list:
    /* empty */
    | statement_list statement
    ;

statement:
    expr SEMI
    | ID ASSIGN expr SEMI
    | ID INC SEMI
    | ID DEC SEMI
    | for_statement
    ;

expr:
    expr PLUS term
    | expr MINUS term
    | term
    ;

term:
    term MUL factor
    | term DIV factor
    | factor
    ;

factor:
    ID
    | NUMBER
    | LPAREN expr RPAREN
    ;

%%

void yyerror(const char *s) {
    syntax_valid = 0;
    fprintf(stderr, "\n>>> RESULT: Invalid 'for' loop syntax! (%s)\n\n", s);
}

int main() {
    printf("======================================================\n");
    printf("       YACC: C 'FOR' STATEMENT SYNTAX CHECKER         \n");
    printf("======================================================\n");
    printf("Enter a C for-loop statement (end with Ctrl+D or Ctrl+Z):\n");
    printf("Example: for(int i = 0; i < 10; i++) { a = a + 1; }\n\n");

    yyparse();
    return 0;
}
