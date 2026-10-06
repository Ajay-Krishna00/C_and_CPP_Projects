#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Operators:
 * 0: '+'
 * 1: '*'
 * 2: 'i' (identifier)
 * 3: '$'
 *
 * Precedence relations:
 * '<' : Yields precedence (Shift)
 * '>' : Takes precedence (Reduce)
 * '=' : Equal precedence
 * 'e' : Error
 * 'a' : Accept
 */

char opOrder[] = {'+', '*', 'i', '$'};
char precTable[4][4] = {
    //  +    *    i    $
    { '>', '<', '<', '>' }, // +
    { '>', '>', '<', '>' }, // *
    { '>', '>', 'e', '>' }, // i
    { '<', '<', '<', 'a' }  // $
};

int getOpIndex(char c) {
    for (int i = 0; i < 4; i++) {
        if (opOrder[i] == c) return i;
    }
    return -1;
}

int getTopTerminalIndex(char stack[], int top) {
    for (int i = top; i >= 0; i--) {
        int idx = getOpIndex(stack[i]);
        if (idx != -1) return i;
    }
    return -1;
}

void printTable() {
    printf("\nOperator Precedence Matrix:\n");
    printf("     +   *   i   $\n");
    for (int i = 0; i < 4; i++) {
        printf(" %c ", opOrder[i]);
        for (int j = 0; j < 4; j++) {
            printf("  %c ", precTable[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void parse(const char *inputStr) {
    char stack[100];
    int top = 0;
    stack[top] = '$';
    stack[top + 1] = '\0';

    int ip = 0;
    int len = strlen(inputStr);

    printf("%-20s %-10s %-20s %-20s\n", "Stack", "Relation", "Input Buffer", "Action");
    printf("-----------------------------------------------------------------------\n");

    while (1) {
        int termPos = getTopTerminalIndex(stack, top);
        char topTerm = stack[termPos];
        char currInput = inputStr[ip];

        int row = getOpIndex(topTerm);
        int col = getOpIndex(currInput);

        if (row == -1 || col == -1) {
            printf("\n>>> Parsing FAILED: Invalid character '%c'\n", currInput);
            return;
        }

        char relation = precTable[row][col];

        char relStr[5] = {relation, '\0'};
        printf("%-20s %-10s %-20s ", stack, relStr, inputStr + ip);

        if (relation == '<' || relation == '=') {
            // Shift
            top++;
            stack[top] = currInput;
            stack[top + 1] = '\0';
            ip++;
            printf("Shift '%c'\n", currInput);
        } else if (relation == '>') {
            // Reduce
            // Handle 'i' -> 'E'
            if (stack[top] == 'i') {
                stack[top] = 'E';
                printf("Reduce E -> i\n");
            }
            // Handle 'E+E' or 'E*E'
            else if (top >= 2 && (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E' && stack[top - 2] == 'E') {
                char op = stack[top - 1];
                top -= 2;
                stack[top] = 'E';
                stack[top + 1] = '\0';
                printf("Reduce E -> E %c E\n", op);
            } else {
                printf("Error: No reduction rule found\n");
                return;
            }
        } else if (relation == 'a') {
            if (top == 1 && stack[1] == 'E') {
                printf("ACCEPT (Successful Parse)\n");
            } else {
                printf("Error: Incomplete parse\n");
            }
            return;
        } else {
            printf("ERROR (Syntax Error)\n");
            return;
        }
    }
}

int main() {
    printf("======================================================\n");
    printf("     OPERATOR PRECEDENCE PARSER (CYCLE III)           \n");
    printf("     Grammar: E -> E + E | E * E | i                  \n");
    printf("======================================================\n");

    printTable();

    printf("1. Test default valid expression: i+i*i$\n");
    printf("2. Test expression: i*i+i$\n");
    printf("3. Enter custom expression (must end with $ and use i, +, *)\n");
    printf("Enter choice (1, 2, or 3): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    char input[100];
    if (choice == 1) {
        strcpy(input, "i+i*i$");
    } else if (choice == 2) {
        strcpy(input, "i*i+i$");
    } else {
        printf("Enter expression ending with '$' (e.g., i+i$): ");
        scanf("%s", input);
        if (input[strlen(input) - 1] != '$') {
            strcat(input, "$");
        }
    }

    printf("\nParsing input: %s\n\n", input);
    parse(input);

    return 0;
}
