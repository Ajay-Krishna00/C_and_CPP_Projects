%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ASTNode {
    char val[32];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode* createNode(const char *val, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    strncpy(node->val, val, 31);
    node->val[31] = '\0';
    node->left = left;
    node->right = right;
    return node;
}

void printAST(ASTNode *root, int depth) {
    if (root == NULL) return;
    printAST(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("[%s]\n", root->val);
    printAST(root->left, depth + 1);
}

void printPreorder(ASTNode *root) {
    if (root == NULL) return;
    printf("%s ", root->val);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(ASTNode *root) {
    if (root == NULL) return;
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%s ", root->val);
}

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char str[32];
    struct ASTNode *node;
}

%token <str> NUMBER ID
%token ADD SUB MUL DIV ASSIGN LPAREN RPAREN NL
%type <node> stmt expr term factor

%%

program:
    /* empty */
    | program line
    ;

line:
    NL
    | stmt NL {
        printf("\n================ ABSTRACT SYNTAX TREE ================\n");
        printf("Hierarchical Representation (rotated view, root at left):\n\n");
        printAST($1, 0);
        printf("\nPre-order Traversal (Prefix): ");
        printPreorder($1);
        printf("\nPost-order Traversal (Postfix): ");
        printPostorder($1);
        printf("\n======================================================\n\n");
        printf("Enter an expression/assignment (e.g., a = b + c * 5): ");
    }
    | error NL {
        yyerrok;
        printf("Enter an expression/assignment: ");
    }
    ;

stmt:
    ID ASSIGN expr   { $$ = createNode("=", createNode($1, NULL, NULL), $3); }
    | expr           { $$ = $1; }
    ;

expr:
    expr ADD term    { $$ = createNode("+", $1, $3); }
    | expr SUB term   { $$ = createNode("-", $1, $3); }
    | term            { $$ = $1; }
    ;

term:
    term MUL factor   { $$ = createNode("*", $1, $3); }
    | term DIV factor  { $$ = createNode("/", $1, $3); }
    | factor          { $$ = $1; }
    ;

factor:
    LPAREN expr RPAREN { $$ = $2; }
    | ID               { $$ = createNode($1, NULL, NULL); }
    | NUMBER           { $$ = createNode($1, NULL, NULL); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, " -> Parse Error: %s\n", s);
}

int main() {
    printf("======================================================\n");
    printf("     BNF TO YACC: ABSTRACT SYNTAX TREE GENERATOR      \n");
    printf("======================================================\n");
    printf("Enter an expression/assignment (e.g., a = b + c * 5): ");
    yyparse();
    return 0;
}
