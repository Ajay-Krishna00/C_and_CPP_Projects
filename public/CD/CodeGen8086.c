#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 50
#define MAX_VARS 50

char variables[MAX_VARS][20];
int varCount = 0;

void addVariable(const char *name) {
    if (isdigit(name[0])) return; // numeric literal
    if (strcmp(name, "") == 0) return;

    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i], name) == 0) return;
    }
    strcpy(variables[varCount++], name);
}

void trim(char *str) {
    int i = 0, j = strlen(str) - 1;
    while (isspace(str[i])) i++;
    while (j >= 0 && isspace(str[j])) j--;
    str[j + 1] = '\0';
    memmove(str, str + i, j - i + 2);
}

void generate8086Assembly(char tac[][100], int n) {
    varCount = 0;

    // Scan variables from TAC
    for (int i = 0; i < n; i++) {
        char line[100];
        strcpy(line, tac[i]);
        char *token = strtok(line, " =+-*/><!\t\n;");
        while (token != NULL) {
            if (strcmp(token, "if") != 0 && strcmp(token, "goto") != 0 &&
                token[strlen(token) - 1] != ':') {
                addVariable(token);
            }
            token = strtok(NULL, " =+-*/><!\t\n;");
        }
    }

    printf("\n======================================================\n");
    printf("         GENERATED 8086 ASSEMBLY CODE                 \n");
    printf("======================================================\n");

    printf(".MODEL SMALL\n");
    printf(".STACK 100H\n\n");

    printf(".DATA\n");
    for (int i = 0; i < varCount; i++) {
        printf("    %-10s DW ?\n", variables[i]);
    }
    printf("\n.CODE\n");
    printf("MAIN PROC\n");
    printf("    MOV AX, @DATA\n");
    printf("    MOV DS, AX\n\n");

    for (int i = 0; i < n; i++) {
        char stmt[100];
        strcpy(stmt, tac[i]);
        trim(stmt);

        if (strlen(stmt) == 0) continue;

        printf("    ; TAC: %s\n", stmt);

        // Case 1: Label declaration (e.g. L1:)
        if (stmt[strlen(stmt) - 1] == ':') {
            printf("%s\n", stmt);
            continue;
        }

        // Case 2: Conditional jump: if a < b goto L1
        if (strncmp(stmt, "if", 2) == 0) {
            char arg1[20], rel[5], arg2[20], gotoKw[10], targetLabel[20];
            if (sscanf(stmt, "if %s %s %s %s %s", arg1, rel, arg2, gotoKw, targetLabel) >= 4) {
                printf("    MOV AX, %s\n", arg1);
                printf("    CMP AX, %s\n", arg2);
                if (strcmp(rel, "<") == 0) printf("    JL  %s\n\n", targetLabel);
                else if (strcmp(rel, "<=") == 0) printf("    JLE %s\n\n", targetLabel);
                else if (strcmp(rel, ">") == 0) printf("    JG  %s\n\n", targetLabel);
                else if (strcmp(rel, ">=") == 0) printf("    JGE %s\n\n", targetLabel);
                else if (strcmp(rel, "==") == 0) printf("    JE  %s\n\n", targetLabel);
                else if (strcmp(rel, "!=") == 0) printf("    JNE %s\n\n", targetLabel);
                else printf("    JMP %s\n\n", targetLabel);
                continue;
            }
        }

        // Case 3: Unconditional jump: goto L1
        if (strncmp(stmt, "goto", 4) == 0) {
            char label[20];
            sscanf(stmt, "goto %s", label);
            printf("    JMP %s\n\n", label);
            continue;
        }

        // Case 4: Binary / Unary arithmetic or simple assignment
        char res[20], op1[20], op2[20], op;
        if (sscanf(stmt, "%s = %s %c %s", res, op1, &op, op2) == 4) {
            printf("    MOV AX, %s\n", op1);
            if (op == '+') {
                printf("    ADD AX, %s\n", op2);
            } else if (op == '-') {
                printf("    SUB AX, %s\n", op2);
            } else if (op == '*') {
                printf("    MOV BX, %s\n", op2);
                printf("    IMUL BX\n");
            } else if (op == '/') {
                printf("    CWD\n");
                printf("    MOV BX, %s\n", op2);
                printf("    IDIV BX\n");
            }
            printf("    MOV %s, AX\n\n", res);
        } else if (sscanf(stmt, "%s = %s", res, op1) == 2) {
            // Simple assignment: x = y
            printf("    MOV AX, %s\n", op1);
            printf("    MOV %s, AX\n\n", res);
        }
    }

    printf("    ; Return to DOS\n");
    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");
    printf("MAIN ENDP\n");
    printf("END MAIN\n");
    printf("======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("   8086 ASSEMBLY CODE GENERATOR (CYCLE IV)            \n");
    printf("   Backend: Three Address Code -> 8086 Assembly       \n");
    printf("======================================================\n");

    printf("1. Run with built-in standard TAC example:\n");
    printf("     t1 = a + b\n");
    printf("     t2 = c * d\n");
    printf("     t3 = t1 - t2\n");
    printf("     if t3 <= 0 goto L1\n");
    printf("     res = t3\n");
    printf("     goto L2\n");
    printf("     L1:\n");
    printf("     res = 0\n");
    printf("     L2:\n");
    printf("2. Enter custom Three Address Code statements\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    char tac[MAX_LINES][100];
    int n = 0;

    if (choice == 1) {
        strcpy(tac[n++], "t1 = a + b");
        strcpy(tac[n++], "t2 = c * d");
        strcpy(tac[n++], "t3 = t1 - t2");
        strcpy(tac[n++], "if t3 <= 0 goto L1");
        strcpy(tac[n++], "res = t3");
        strcpy(tac[n++], "goto L2");
        strcpy(tac[n++], "L1:");
        strcpy(tac[n++], "res = 0");
        strcpy(tac[n++], "L2:");
    } else {
        printf("Enter number of TAC statements: ");
        scanf("%d", &n);
        getchar(); // clear newline
        printf("Enter statements (one per line):\n");
        for (int i = 0; i < n; i++) {
            fgets(tac[i], sizeof(tac[i]), stdin);
            tac[i][strcspn(tac[i], "\r\n")] = 0;
        }
    }

    generate8086Assembly(tac, n);

    return 0;
}
