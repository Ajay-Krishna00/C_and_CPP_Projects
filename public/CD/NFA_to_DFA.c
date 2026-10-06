#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NFA_STATES 20
#define MAX_DFA_STATES 50
#define MAX_SYMBOLS 10

typedef struct {
    int states[MAX_NFA_STATES];
    int count;
    char name; // A, B, C...
    int isFinal;
} DFAState;

int numNfaStates, numSymbols;
char alphabet[MAX_SYMBOLS];
int isNfaFinal[MAX_NFA_STATES];

// NFA transitions: nfaTrans[from][sym][to] = 1
int nfaTrans[MAX_NFA_STATES][MAX_SYMBOLS][MAX_NFA_STATES];

DFAState dfaStates[MAX_DFA_STATES];
int numDfaStates = 0;
int dfaTrans[MAX_DFA_STATES][MAX_SYMBOLS]; // -1 for dead/none

// Helper to check if two state sets are identical
int areStateSetsEqual(int set1[], int count1, int set2[], int count2) {
    if (count1 != count2) return 0;
    for (int i = 0; i < count1; i++) {
        if (set1[i] != set2[i]) return 0;
    }
    return 1;
}

// Find if a state set already exists in dfaStates
int findDfaStateIndex(int set[], int count) {
    for (int i = 0; i < numDfaStates; i++) {
        if (areStateSetsEqual(dfaStates[i].states, dfaStates[i].count, set, count)) {
            return i;
        }
    }
    return -1;
}

void sortSet(int set[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (set[i] > set[j]) {
                int t = set[i];
                set[i] = set[j];
                set[j] = t;
            }
        }
    }
}

void convertNfaToDfa() {
    numDfaStates = 0;

    // Initial state: { q0 }
    DFAState initial;
    initial.count = 1;
    initial.states[0] = 0; // q0
    initial.name = 'A';
    initial.isFinal = isNfaFinal[0];

    dfaStates[numDfaStates++] = initial;

    int currentIdx = 0;
    while (currentIdx < numDfaStates) {
        DFAState curr = dfaStates[currentIdx];

        for (int a = 0; a < numSymbols; a++) {
            int unionSet[MAX_NFA_STATES] = {0};
            int unionCount = 0;
            int mark[MAX_NFA_STATES] = {0};

            // Compute delta(curr, a)
            for (int i = 0; i < curr.count; i++) {
                int s = curr.states[i];
                for (int next = 0; next < numNfaStates; next++) {
                    if (nfaTrans[s][a][next] && !mark[next]) {
                        mark[next] = 1;
                        unionSet[unionCount++] = next;
                    }
                }
            }

            if (unionCount == 0) {
                dfaTrans[currentIdx][a] = -1; // Dead transition
                continue;
            }

            sortSet(unionSet, unionCount);

            int existingIdx = findDfaStateIndex(unionSet, unionCount);
            if (existingIdx == -1) {
                // New DFA state
                DFAState newState;
                newState.count = unionCount;
                for (int k = 0; k < unionCount; k++) {
                    newState.states[k] = unionSet[k];
                }
                newState.name = 'A' + numDfaStates;

                // Check if final
                newState.isFinal = 0;
                for (int k = 0; k < unionCount; k++) {
                    if (isNfaFinal[newState.states[k]]) {
                        newState.isFinal = 1;
                        break;
                    }
                }

                existingIdx = numDfaStates;
                dfaStates[numDfaStates++] = newState;
            }

            dfaTrans[currentIdx][a] = existingIdx;
        }

        currentIdx++;
    }
}

void printDfa() {
    printf("\n======================================================\n");
    printf("                  EQUIVALENT DFA                      \n");
    printf("======================================================\n");
    printf("%-10s %-22s", "DFA State", "NFA States");
    for (int a = 0; a < numSymbols; a++) {
        char header[20];
        snprintf(header, sizeof(header), "Input '%c'", alphabet[a]);
        printf("%-15s", header);
    }
    printf("\n------------------------------------------------------\n");

    for (int i = 0; i < numDfaStates; i++) {
        char label[20];
        snprintf(label, sizeof(label), "%c %c%s",
                 (i == 0 ? '>' : ' '),
                 dfaStates[i].name,
                 (dfaStates[i].isFinal ? "*" : " "));
        printf("%-10s", label);

        // Print NFA state set
        char setStr[50] = "{ ";
        for (int k = 0; k < dfaStates[i].count; k++) {
            char temp[10];
            snprintf(temp, sizeof(temp), "q%d%s", dfaStates[i].states[k], (k < dfaStates[i].count - 1 ? ", " : ""));
            strcat(setStr, temp);
        }
        strcat(setStr, " }");
        printf("%-22s", setStr);

        // Print transitions
        for (int a = 0; a < numSymbols; a++) {
            int toIdx = dfaTrans[i][a];
            if (toIdx == -1) {
                printf("%-15s", "Phi");
            } else {
                char target[10];
                snprintf(target, sizeof(target), "%c", dfaStates[toIdx].name);
                printf("%-15s", target);
            }
        }
        printf("\n");
    }

    printf("\nStart State: A\nFinal States: ");
    for (int i = 0; i < numDfaStates; i++) {
        if (dfaStates[i].isFinal) {
            printf("%c ", dfaStates[i].name);
        }
    }
    printf("\n======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("          CONVERT NFA TO DFA (CYCLE I)                \n");
    printf("======================================================\n");
    printf("1. Run with standard sample NFA (ends with 'ab')\n");
    printf("2. Enter custom NFA details\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    memset(nfaTrans, 0, sizeof(nfaTrans));
    memset(isNfaFinal, 0, sizeof(isNfaFinal));

    if (choice == 1) {
        numNfaStates = 3;
        numSymbols = 2;
        alphabet[0] = 'a';
        alphabet[1] = 'b';
        isNfaFinal[2] = 1; // q2 is final

        // q0 on a -> {q0, q1}
        nfaTrans[0][0][0] = 1;
        nfaTrans[0][0][1] = 1;
        // q0 on b -> {q0}
        nfaTrans[0][1][0] = 1;
        // q1 on b -> {q2}
        nfaTrans[1][1][2] = 1;

        printf("\nUsing Sample NFA (language of strings ending with 'ab'):\n");
        printf("States: q0, q1, q2 (Final state: q2)\n");
        printf("Transitions:\n");
        printf("  delta(q0, a) = { q0, q1 }\n");
        printf("  delta(q0, b) = { q0 }\n");
        printf("  delta(q1, b) = { q2 }\n");
    } else {
        printf("Enter number of NFA states: ");
        scanf("%d", &numNfaStates);

        printf("Enter number of alphabet symbols: ");
        scanf("%d", &numSymbols);

        printf("Enter alphabet symbols (e.g., a b): ");
        for (int i = 0; i < numSymbols; i++) {
            scanf(" %c", &alphabet[i]);
        }

        int numFinal;
        printf("Enter number of final states: ");
        scanf("%d", &numFinal);
        printf("Enter final state indices (e.g. 2 for q2): ");
        for (int i = 0; i < numFinal; i++) {
            int fs;
            scanf("%d", &fs);
            isNfaFinal[fs] = 1;
        }

        int numTrans;
        printf("Enter number of transitions: ");
        scanf("%d", &numTrans);
        printf("Enter transitions (<from_state> <symbol> <to_state>):\n");
        for (int i = 0; i < numTrans; i++) {
            int u, v;
            char sym;
            scanf("%d %c %d", &u, &sym, &v);
            for (int s = 0; s < numSymbols; s++) {
                if (alphabet[s] == sym) {
                    nfaTrans[u][s][v] = 1;
                    break;
                }
            }
        }
    }

    convertNfaToDfa();
    printDfa();

    return 0;
}
