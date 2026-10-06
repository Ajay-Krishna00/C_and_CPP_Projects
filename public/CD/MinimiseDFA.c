#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 30
#define MAX_SYMBOLS 10

int numStates, numSymbols;
char alphabet[MAX_SYMBOLS];
int dfaTrans[MAX_STATES][MAX_SYMBOLS];
int isFinal[MAX_STATES];

int group[MAX_STATES];       // group[i] = group id of state i
int newGroup[MAX_STATES];
int numGroups = 0;

void minimizeDFA() {
    // 1. Initial partition: Final states vs Non-final states
    int hasFinal = 0, hasNonFinal = 0;
    for (int i = 0; i < numStates; i++) {
        if (isFinal[i]) {
            group[i] = 1;
            hasFinal = 1;
        } else {
            group[i] = 0;
            hasNonFinal = 0; // group 0
        }
    }

    if (hasFinal && hasNonFinal) {
        numGroups = 2;
    } else {
        // All states are final or all are non-final
        for (int i = 0; i < numStates; i++) group[i] = 0;
        numGroups = 1;
    }

    // 2. Iterative refinement
    int changed = 1;
    while (changed) {
        changed = 0;
        int nextGroupCount = 0;

        for (int i = 0; i < numStates; i++) {
            newGroup[i] = -1;
        }

        for (int i = 0; i < numStates; i++) {
            if (newGroup[i] != -1) continue;

            // State i starts a new partition in this iteration
            newGroup[i] = nextGroupCount;

            for (int j = i + 1; j < numStates; j++) {
                if (newGroup[j] != -1) continue;

                // Check if state i and state j are equivalent under current grouping
                if (group[i] == group[j]) {
                    int identical = 1;
                    for (int a = 0; a < numSymbols; a++) {
                        int dest_i = dfaTrans[i][a];
                        int dest_j = dfaTrans[j][a];
                        if (group[dest_i] != group[dest_j]) {
                            identical = 0;
                            break;
                        }
                    }
                    if (identical) {
                        newGroup[j] = nextGroupCount;
                    }
                }
            }
            nextGroupCount++;
        }

        if (nextGroupCount != numGroups) {
            changed = 1;
        }

        for (int i = 0; i < numStates; i++) {
            group[i] = newGroup[i];
        }
        numGroups = nextGroupCount;
    }
}

void printMinimizedDFA() {
    printf("\n======================================================\n");
    printf("                 EQUIVALENCE CLASSES                  \n");
    printf("======================================================\n");
    for (int g = 0; g < numGroups; g++) {
        printf("Group %d (State S%d): { ", g, g);
        int first = 1;
        for (int i = 0; i < numStates; i++) {
            if (group[i] == g) {
                if (!first) printf(", ");
                printf("q%d", i);
                first = 0;
            }
        }
        printf(" }\n");
    }

    printf("\n======================================================\n");
    printf("                 MINIMIZED DFA TABLE                  \n");
    printf("======================================================\n");
    printf("%-12s", "State");
    for (int a = 0; a < numSymbols; a++) {
        char col[20];
        snprintf(col, sizeof(col), "Input '%c'", alphabet[a]);
        printf("%-15s", col);
    }
    printf("\n------------------------------------------------------\n");

    int minFinal[MAX_STATES] = {0};
    int minStart = group[0];

    for (int i = 0; i < numStates; i++) {
        if (isFinal[i]) {
            minFinal[group[i]] = 1;
        }
    }

    for (int g = 0; g < numGroups; g++) {
        // Pick representative state for group g
        int rep = -1;
        for (int i = 0; i < numStates; i++) {
            if (group[i] == g) {
                rep = i;
                break;
            }
        }

        char label[20];
        snprintf(label, sizeof(label), "%sS%d%s",
                 (g == minStart ? "->" : "  "),
                 g,
                 (minFinal[g] ? "*" : " "));
        printf("%-12s", label);

        for (int a = 0; a < numSymbols; a++) {
            int destState = dfaTrans[rep][a];
            int destGroup = group[destState];
            char target[10];
            snprintf(target, sizeof(target), "S%d", destGroup);
            printf("%-15s", target);
        }
        printf("\n");
    }

    printf("\nStart State: S%d\nFinal State(s): ", minStart);
    for (int g = 0; g < numGroups; g++) {
        if (minFinal[g]) printf("S%d ", g);
    }
    printf("\n======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("           DFA MINIMIZATION (CYCLE I)                 \n");
    printf("======================================================\n");
    printf("1. Run with standard sample DFA (5 states)\n");
    printf("2. Enter custom DFA details\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    memset(isFinal, 0, sizeof(isFinal));

    if (choice == 1) {
        // Standard textbook example:
        // States: q0, q1, q2, q3, q4. Final: q1, q2, q4
        // Symbols: 0, 1
        numStates = 5;
        numSymbols = 2;
        alphabet[0] = '0';
        alphabet[1] = '1';

        isFinal[1] = 1;
        isFinal[2] = 1;
        isFinal[4] = 1;

        // Transitions:
        dfaTrans[0][0] = 1; dfaTrans[0][1] = 3; // q0 -> q1, q3
        dfaTrans[1][0] = 2; dfaTrans[1][1] = 4; // q1 -> q2, q4
        dfaTrans[2][0] = 1; dfaTrans[2][1] = 4; // q2 -> q1, q4
        dfaTrans[3][0] = 2; dfaTrans[3][1] = 4; // q3 -> q2, q4
        dfaTrans[4][0] = 4; dfaTrans[4][1] = 4; // q4 -> q4, q4

        printf("\nUsing Sample 5-state DFA:\n");
        printf("States: q0, q1, q2, q3, q4\nAlphabet: '0', '1'\nFinal states: q1, q2, q4\n");
    } else {
        printf("Enter total number of states: ");
        scanf("%d", &numStates);

        printf("Enter total number of input symbols: ");
        scanf("%d", &numSymbols);

        printf("Enter symbols (e.g. 0 1): ");
        for (int i = 0; i < numSymbols; i++) {
            scanf(" %c", &alphabet[i]);
        }

        int fCount;
        printf("Enter number of final states: ");
        scanf("%d", &fCount);
        printf("Enter final state indices (0 to %d): ", numStates - 1);
        for (int i = 0; i < fCount; i++) {
            int fs;
            scanf("%d", &fs);
            isFinal[fs] = 1;
        }

        printf("Enter transition table (state destination for each input symbol):\n");
        for (int i = 0; i < numStates; i++) {
            for (int a = 0; a < numSymbols; a++) {
                printf("delta(q%d, '%c') = q", i, alphabet[a]);
                scanf("%d", &dfaTrans[i][a]);
            }
        }
    }

    minimizeDFA();
    printMinimizedDFA();

    return 0;
}
