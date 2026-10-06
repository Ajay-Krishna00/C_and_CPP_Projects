#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_ALPHABET 10

int numStates, numSymbols;
char alphabet[MAX_ALPHABET];
int numFinalStates;
int finalStates[MAX_STATES];
int isOriginalFinal[MAX_STATES];

// Transitions: trans[from][symbol_index][to] = 1
// Symbol index: 0..numSymbols-1 for regular symbols, numSymbols for epsilon ('e')
int trans[MAX_STATES][MAX_ALPHABET + 1][MAX_STATES];
int epsClosure[MAX_STATES][MAX_STATES];

// Converted NFA transitions: newTrans[from][symbol_index][to] = 1
int newTrans[MAX_STATES][MAX_ALPHABET][MAX_STATES];
int isNewFinal[MAX_STATES];

void findEpsilonClosure(int startState, int currState) {
    epsClosure[startState][currState] = 1;
    int epsIdx = numSymbols; // epsilon index

    for (int next = 0; next < numStates; next++) {
        if (trans[currState][epsIdx][next] && !epsClosure[startState][next]) {
            findEpsilonClosure(startState, next);
        }
    }
}

void computeEpsilonClosures() {
    memset(epsClosure, 0, sizeof(epsClosure));
    for (int i = 0; i < numStates; i++) {
        findEpsilonClosure(i, i);
    }
}

void convertToNFAWithoutEpsilon() {
    memset(newTrans, 0, sizeof(newTrans));
    memset(isNewFinal, 0, sizeof(isNewFinal));

    // 1. Calculate new transitions:
    // delta'(q, a) = eps-closure(delta(eps-closure(q), a))
    for (int q = 0; q < numStates; q++) {
        for (int a = 0; a < numSymbols; a++) {
            int reachableOnA[MAX_STATES] = {0};

            // Step A: delta(eps-closure(q), a)
            for (int s1 = 0; s1 < numStates; s1++) {
                if (epsClosure[q][s1]) {
                    for (int s2 = 0; s2 < numStates; s2++) {
                        if (trans[s1][a][s2]) {
                            reachableOnA[s2] = 1;
                        }
                    }
                }
            }

            // Step B: eps-closure of the above reachable states
            for (int s2 = 0; s2 < numStates; s2++) {
                if (reachableOnA[s2]) {
                    for (int s3 = 0; s3 < numStates; s3++) {
                        if (epsClosure[s2][s3]) {
                            newTrans[q][a][s3] = 1;
                        }
                    }
                }
            }
        }
    }

    // 2. Calculate new final states:
    // A state q is final if eps-closure(q) contains any original final state
    for (int q = 0; q < numStates; q++) {
        for (int s = 0; s < numStates; s++) {
            if (epsClosure[q][s] && isOriginalFinal[s]) {
                isNewFinal[q] = 1;
                break;
            }
        }
    }
}

void printResults() {
    printf("\n======================================================\n");
    printf("                  EPSILON CLOSURES                    \n");
    printf("======================================================\n");
    for (int i = 0; i < numStates; i++) {
        printf("e-closure(q%d) = { ", i);
        int first = 1;
        for (int j = 0; j < numStates; j++) {
            if (epsClosure[i][j]) {
                if (!first) printf(", ");
                printf("q%d", j);
                first = 0;
            }
        }
        printf(" }\n");
    }

    printf("\n======================================================\n");
    printf("         CONVERTED NFA WITHOUT EPSILON TRANSITIONS    \n");
    printf("======================================================\n");
    printf("%-10s", "State");
    for (int a = 0; a < numSymbols; a++) {
        char header[20];
        snprintf(header, sizeof(header), "delta(q, %c)", alphabet[a]);
        printf("%-20s", header);
    }
    printf("\n------------------------------------------------------\n");

    for (int q = 0; q < numStates; q++) {
        char stateLabel[20];
        snprintf(stateLabel, sizeof(stateLabel), "%sq%d%s",
                 (q == 0 ? "->" : "  "),
                 q,
                 (isNewFinal[q] ? "*" : " "));
        printf("%-10s", stateLabel);

        for (int a = 0; a < numSymbols; a++) {
            char setStr[100] = "{ ";
            int hasAny = 0;
            for (int to = 0; to < numStates; to++) {
                if (newTrans[q][a][to]) {
                    char temp[10];
                    snprintf(temp, sizeof(temp), "%sq%d", (hasAny ? ", " : ""), to);
                    strcat(setStr, temp);
                    hasAny = 1;
                }
            }
            if (!hasAny) strcat(setStr, "Phi");
            strcat(setStr, " }");
            printf("%-20s", setStr);
        }
        printf("\n");
    }

    printf("\nInitial State: q0\nFinal States : { ");
    int firstF = 1;
    for (int q = 0; q < numStates; q++) {
        if (isNewFinal[q]) {
            if (!firstF) printf(", ");
            printf("q%d", q);
            firstF = 0;
        }
    }
    printf(" }\n======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("       CONVERT NFA WITH e TO NFA WITHOUT e (CYCLE I)  \n");
    printf("======================================================\n");
    printf("1. Run with built-in standard example\n");
    printf("2. Enter custom NFA with epsilon transitions\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    memset(trans, 0, sizeof(trans));
    memset(isOriginalFinal, 0, sizeof(isOriginalFinal));

    if (choice == 1) {
        numStates = 3;
        numSymbols = 2;
        alphabet[0] = 'a';
        alphabet[1] = 'b';
        isOriginalFinal[2] = 1; // q2 is final

        // Sample transitions:
        // q0 -(a)-> q0, q0 -(e)-> q1
        // q1 -(b)-> q1, q1 -(e)-> q2
        // q2 -(a)-> q2
        trans[0][0][0] = 1; // q0 -a-> q0
        trans[0][2][1] = 1; // q0 -e-> q1 (2 is epsilon)
        trans[1][1][1] = 1; // q1 -b-> q1
        trans[1][2][2] = 1; // q1 -e-> q2
        trans[2][0][2] = 1; // q2 -a-> q2

        printf("\nUsing Sample NFA with e-transitions:\n");
        printf("States: q0, q1, q2 (Final state: q2)\n");
        printf("Alphabet: a, b (e represents epsilon)\n");
        printf("Transitions:\n");
        printf("  q0 --a--> q0\n  q0 --e--> q1\n  q1 --b--> q1\n  q1 --e--> q2\n  q2 --a--> q2\n");
    } else {
        printf("Enter number of states: ");
        scanf("%d", &numStates);

        printf("Enter number of input symbols (excluding epsilon): ");
        scanf("%d", &numSymbols);

        printf("Enter input symbols (space separated, e.g., a b): ");
        for (int i = 0; i < numSymbols; i++) {
            scanf(" %c", &alphabet[i]);
        }

        printf("Enter number of final states: ");
        scanf("%d", &numFinalStates);
        printf("Enter final state indices (e.g., 2 for q2): ");
        for (int i = 0; i < numFinalStates; i++) {
            int fs;
            scanf("%d", &fs);
            isOriginalFinal[fs] = 1;
        }

        int numTrans;
        printf("Enter number of transitions: ");
        scanf("%d", &numTrans);
        printf("Enter transitions (<from_state> <symbol> <to_state>), use 'e' for epsilon:\n");
        for (int i = 0; i < numTrans; i++) {
            int u, v;
            char sym;
            scanf("%d %c %d", &u, &sym, &v);
            if (sym == 'e' || sym == 'E') {
                trans[u][numSymbols][v] = 1;
            } else {
                for (int s = 0; s < numSymbols; s++) {
                    if (alphabet[s] == sym) {
                        trans[u][s][v] = 1;
                        break;
                    }
                }
            }
        }
    }

    computeEpsilonClosures();
    convertToNFAWithoutEpsilon();
    printResults();

    return 0;
}
