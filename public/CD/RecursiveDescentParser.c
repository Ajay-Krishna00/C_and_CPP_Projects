#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Grammar:
 * E  -> T E'
 * E' -> + T E' | - T E' | e
 * T  -> F T'
 * T' -> * F T' | / F T' | e
 * F  -> ( E ) | id (or number)
 */

char input[100];
int cursor = 0;
int hasError = 0;

void E();
void Edash();
void T();
void Tdash();
void F();

void match(char expected) {
    if (input[cursor] == expected) {
        printf("  Matched '%c' at position %d\n", expected, cursor);
        cursor++;
    } else {
        printf("  Error: Expected '%c' but found '%c' at position %d\n",
               expected, input[cursor] ? input[cursor] : '$', cursor);
        hasError = 1;
    }
}

void E() {
    if (hasError) return;
    printf("Enter E (cursor at '%c')\n", input[cursor]);
    T();
    Edash();
    printf("Exit E\n");
}

void Edash() {
    if (hasError) return;
    printf("Enter E' (cursor at '%c')\n", input[cursor]);
    if (input[cursor] == '+' || input[cursor] == '-') {
        char op = input[cursor];
        match(op);
        T();
        Edash();
    } else {
        printf("  E' -> epsilon\n");
    }
    printf("Exit E'\n");
}

void T() {
    if (hasError) return;
    printf("Enter T (cursor at '%c')\n", input[cursor]);
    F();
    Tdash();
    printf("Exit T\n");
}

void Tdash() {
    if (hasError) return;
    printf("Enter T' (cursor at '%c')\n", input[cursor]);
    if (input[cursor] == '*' || input[cursor] == '/') {
        char op = input[cursor];
        match(op);
        F();
        Tdash();
    } else {
        printf("  T' -> epsilon\n");
    }
    printf("Exit T'\n");
}

void F() {
    if (hasError) return;
    printf("Enter F (cursor at '%c')\n", input[cursor]);
    if (input[cursor] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(input[cursor])) {
        printf("  F -> id ('%c')\n", input[cursor]);
        match(input[cursor]);
    } else {
        printf("  Error in F: Unexpected token '%c' at position %d\n", input[cursor], cursor);
        hasError = 1;
    }
    printf("Exit F\n");
}

void parseExpression(const char *str) {
    strcpy(input, str);
    cursor = 0;
    hasError = 0;

    printf("\n--- Parsing '%s' ---\n", input);
    E();

    if (!hasError && input[cursor] == '\0') {
        printf("\n>>> Result: SUCCESS! The input string is VALID.\n");
    } else {
        printf("\n>>> Result: REJECTED! Syntax error in the input string.\n");
    }
}

int main() {
    printf("======================================================\n");
    printf("         RECURSIVE DESCENT PARSER (CYCLE III)         \n");
    printf("   Grammar:                                           \n");
    printf("     E  -> T E'                                       \n");
    printf("     E' -> + T E' | - T E' | e                        \n");
    printf("     T  -> F T'                                       \n");
    printf("     T' -> * F T' | / F T' | e                        \n");
    printf("     F  -> ( E ) | id                                 \n");
    printf("======================================================\n");

    printf("1. Test default expression: (i+i)*i\n");
    printf("2. Test invalid expression: i+*i\n");
    printf("3. Enter custom expression\n");
    printf("Enter choice (1, 2, or 3): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    if (choice == 1) {
        parseExpression("(i+i)*i");
    } else if (choice == 2) {
        parseExpression("i+*i");
    } else {
        char custom[100];
        printf("Enter expression (e.g. i+i*i or (a+b)*c): ");
        scanf("%s", custom);
        parseExpression(custom);
    }

    return 0;
}
