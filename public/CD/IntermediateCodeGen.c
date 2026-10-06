#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char op[10];
    char arg1[20];
    char arg2[20];
    char res[20];
} Quadruple;

Quadruple quads[MAX];
int quadCount = 0;
int tempVarCount = 1;

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

// Convert infix expression to postfix
void infixToPostfix(const char *infix, char postfix[][20], int *postLen) {
    char stack[MAX];
    int top = -1;
    *postLen = 0;

    int i = 0;
    while (infix[i] != '\0') {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        // Operand (variable or number)
        if (isalnum(infix[i])) {
            char operand[20];
            int k = 0;
            while (isalnum(infix[i])) {
                operand[k++] = infix[i++];
            }
            operand[k] = '\0';
            strcpy(postfix[(*postLen)++], operand);
            continue;
        }

        if (infix[i] == '(') {
            stack[++top] = '(';
            i++;
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                char opStr[2] = {stack[top--], '\0'};
                strcpy(postfix[(*postLen)++], opStr);
            }
            if (top != -1) top--; // pop '('
            i++;
        } else if (isOperator(infix[i])) {
            while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(infix[i])) {
                char opStr[2] = {stack[top--], '\0'};
                strcpy(postfix[(*postLen)++], opStr);
            }
            stack[++top] = infix[i++];
        } else {
            i++;
        }
    }

    while (top != -1) {
        char opStr[2] = {stack[top--], '\0'};
        strcpy(postfix[(*postLen)++], opStr);
    }
}

// Generate Three Address Code & Quadruples from postfix tokens
void generateTAC(char postfix[][20], int postLen, const char *targetVar) {
    char opStack[MAX][20];
    int top = -1;
    quadCount = 0;
    tempVarCount = 1;

    for (int i = 0; i < postLen; i++) {
        // If operator
        if (strlen(postfix[i]) == 1 && isOperator(postfix[i][0])) {
            if (top < 1) {
                printf("Error: Invalid expression\n");
                return;
            }
            char arg2[20], arg1[20];
            strcpy(arg2, opStack[top--]);
            strcpy(arg1, opStack[top--]);

            char tempName[20];
            snprintf(tempName, sizeof(tempName), "t%d", tempVarCount++);

            // Add quadruple
            strcpy(quads[quadCount].op, postfix[i]);
            strcpy(quads[quadCount].arg1, arg1);
            strcpy(quads[quadCount].arg2, arg2);
            strcpy(quads[quadCount].res, tempName);
            quadCount++;

            // Push result onto stack
            strcpy(opStack[++top], tempName);
        } else {
            // Operand
            strcpy(opStack[++top], postfix[i]);
        }
    }

    // Final assignment to target variable
    if (targetVar != NULL && strlen(targetVar) > 0 && top == 0) {
        strcpy(quads[quadCount].op, "=");
        strcpy(quads[quadCount].arg1, opStack[top]);
        strcpy(quads[quadCount].arg2, "-");
        strcpy(quads[quadCount].res, targetVar);
        quadCount++;
    }
}

void printTAC() {
    printf("\n======================================================\n");
    printf("         THREE ADDRESS CODE (TAC) INSTRUCTIONS        \n");
    printf("======================================================\n");
    for (int i = 0; i < quadCount; i++) {
        if (strcmp(quads[i].op, "=") == 0) {
            printf("%s = %s\n", quads[i].res, quads[i].arg1);
        } else {
            printf("%s = %s %s %s\n", quads[i].res, quads[i].arg1, quads[i].op, quads[i].arg2);
        }
    }
}

void printQuadruples() {
    printf("\n======================================================\n");
    printf("                  QUADRUPLES TABLE                    \n");
    printf("======================================================\n");
    printf("%-8s %-10s %-12s %-12s %-12s\n", "Index", "Operator", "Argument 1", "Argument 2", "Result");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < quadCount; i++) {
        printf("(%-6d) %-10s %-12s %-12s %-12s\n",
               i, quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].res);
    }
}

void printTriples() {
    printf("\n======================================================\n");
    printf("                   TRIPLES TABLE                      \n");
    printf("======================================================\n");
    printf("%-8s %-10s %-15s %-15s\n", "Index", "Operator", "Argument 1", "Argument 2");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < quadCount; i++) {
        printf("(%-6d) %-10s %-15s %-15s\n",
               i, quads[i].op, quads[i].arg1, quads[i].arg2);
    }
    printf("======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("     INTERMEDIATE CODE GENERATION (CYCLE IV)          \n");
    printf("======================================================\n");

    printf("1. Test sample: x = a + b * c / d\n");
    printf("2. Test sample: result = (a + b) * (c - d)\n");
    printf("3. Enter custom expression (format: var = expr)\n");
    printf("Enter choice (1, 2, or 3): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    char input[100];
    if (choice == 1) {
        strcpy(input, "x = a + b * c / d");
    } else if (choice == 2) {
        strcpy(input, "result = (a + b) * (c - d)");
    } else {
        printf("Enter assignment expression (e.g. w = a + b * c): ");
        getchar(); // clear newline
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\r\n")] = 0;
    }

    printf("\nInput Statement: %s\n", input);

    char targetVar[20] = "";
    char expr[100] = "";

    char *eqSign = strchr(input, '=');
    if (eqSign != NULL) {
        *eqSign = '\0';
        sscanf(input, "%s", targetVar);
        strcpy(expr, eqSign + 1);
    } else {
        strcpy(expr, input);
    }

    char postfix[MAX][20];
    int postLen = 0;

    infixToPostfix(expr, postfix, &postLen);
    generateTAC(postfix, postLen, targetVar);

    printTAC();
    printQuadruples();
    printTriples();

    return 0;
}
