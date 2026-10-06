#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
char input[MAX];
int top = -1;
int i = 0;

void printStatus(const char *action) {
    char stkStr[MAX];
    strncpy(stkStr, stack, top + 1);
    stkStr[top + 1] = '\0';
    printf("%-20s %-20s %-25s\n", stkStr, input + i, action);
}

// Function to check and perform reduction
// Grammar:
// E -> E + E
// E -> E * E
// E -> ( E )
// E -> i
int checkAndReduce() {
    // 1. Check for 'i' -> reduce to 'E'
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        printStatus("Reduce E -> i");
        return 1;
    }

    // 2. Check for '(E)' -> reduce to 'E'
    if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
        top -= 2;
        stack[top] = 'E';
        printStatus("Reduce E -> (E)");
        return 1;
    }

    // 3. Check for 'E+E'
    // In simple LR/precedence without lookahead ambiguity, we can reduce E+E or E*E
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
        // If next input token is '*', shift has higher precedence; otherwise reduce
        if (input[i] == '*') {
            return 0; // Prefer shift for '*' precedence
        }
        top -= 2;
        stack[top] = 'E';
        printStatus("Reduce E -> E + E");
        return 1;
    }

    // 4. Check for 'E*E'
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
        top -= 2;
        stack[top] = 'E';
        printStatus("Reduce E -> E * E");
        return 1;
    }

    return 0;
}

void parseShiftReduce(const char *inStr) {
    strcpy(input, inStr);
    top = -1;
    i = 0;

    // Push initial marker '$'
    stack[++top] = '$';
    stack[top + 1] = '\0';

    printf("\n%-20s %-20s %-25s\n", "Stack", "Input Buffer", "Action");
    printf("-----------------------------------------------------------------\n");
    printStatus("Initial");

    while (1) {
        // First try reduction
        if (checkAndReduce()) {
            continue;
        }

        // Check accept condition: Stack is "$E" and Input is "$"
        if (top == 1 && stack[0] == '$' && stack[1] == 'E' && input[i] == '$') {
            printStatus("ACCEPT (Successful)");
            printf("\n>>> RESULT: The string is successfully parsed and ACCEPTED!\n\n");
            return;
        }

        // Shift next symbol if available
        if (input[i] != '$' && input[i] != '\0') {
            char ch = input[i++];
            stack[++top] = ch;
            stack[top + 1] = '\0';

            char act[50];
            snprintf(act, sizeof(act), "Shift '%c'", ch);
            printStatus(act);
        } else {
            // Reached end of input and no more reductions possible
            printStatus("REJECT (Syntax Error)");
            printf("\n>>> RESULT: Parsing FAILED / String REJECTED!\n\n");
            return;
        }
    }
}

int main() {
    printf("======================================================\n");
    printf("         SHIFT REDUCE PARSER (CYCLE III)              \n");
    printf("   Grammar:                                           \n");
    printf("     E -> E + E                                       \n");
    printf("     E -> E * E                                       \n");
    printf("     E -> ( E )                                       \n");
    printf("     E -> i                                           \n");
    printf("======================================================\n");

    printf("1. Test default expression: i+i*i$\n");
    printf("2. Test parenthesized expression: (i+i)*i$\n");
    printf("3. Enter custom expression\n");
    printf("Enter choice (1, 2, or 3): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    char inStr[MAX];
    if (choice == 1) {
        strcpy(inStr, "i+i*i$");
    } else if (choice == 2) {
        strcpy(inStr, "(i+i)*i$");
    } else {
        printf("Enter string ending with '$' (using i, +, *, (, )): ");
        scanf("%s", inStr);
        if (inStr[strlen(inStr) - 1] != '$') {
            strcat(inStr, "$");
        }
    }

    parseShiftReduce(inStr);
    return 0;
}
