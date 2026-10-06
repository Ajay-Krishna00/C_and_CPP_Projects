#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_TRANSITIONS 100

typedef struct {
    int from;
    char symbol;
    int to;
} Transition;

int numStates, numTransitions;
Transition transitions[MAX_TRANSITIONS];
int closure[MAX_STATES][MAX_STATES]; // closure[i][j] = 1 if state j in closure of state i
int visited[MAX_STATES];

void findEpsilonClosure(int startState, int currentState) {
    closure[startState][currentState] = 1;

    for (int i = 0; i < numTransitions; i++) {
        // 'e' or 'E' or '3' (often used for epsilon in lab keyboards)
        if (transitions[i].from == currentState &&
           (transitions[i].symbol == 'e' || transitions[i].symbol == 'E' || transitions[i].symbol == '@')) {
            int nextState = transitions[i].to;
            if (!closure[startState][nextState]) {
                findEpsilonClosure(startState, nextState);
            }
        }
    }
}

void computeAllClosures() {
    memset(closure, 0, sizeof(closure));

    for (int state = 0; state < numStates; state++) {
        findEpsilonClosure(state, state);
    }
}

void printClosures() {
    printf("\n======================================================\n");
    printf("              EPSILON (e) CLOSURE OF STATES           \n");
    printf("======================================================\n");
    for (int i = 0; i < numStates; i++) {
        printf("e-closure(q%d) = { ", i);
        int first = 1;
        for (int j = 0; j < numStates; j++) {
            if (closure[i][j]) {
                if (!first) printf(", ");
                printf("q%d", j);
                first = 0;
            }
        }
        printf(" }\n");
    }
    printf("======================================================\n");
}

int main() {
    printf("======================================================\n");
    printf("          EPSILON-CLOSURE FINDER (CYCLE I)            \n");
    printf("======================================================\n");
    printf("1. Run with standard sample NFA-e (q0 -(e)-> q1, q1 -(e)-> q2, q1 -(a)-> q1)\n");
    printf("2. Enter custom NFA-e details\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    if (choice == 1) {
        numStates = 3;
        numTransitions = 4;
        transitions[0] = (Transition){0, 'e', 1}; // q0 -> q1 (e)
        transitions[1] = (Transition){1, 'e', 2}; // q1 -> q2 (e)
        transitions[2] = (Transition){1, 'a', 1}; // q1 -> q1 (a)
        transitions[3] = (Transition){2, 'b', 2}; // q2 -> q2 (b)

        printf("\nUsing Sample NFA with %d states and %d transitions:\n", numStates, numTransitions);
        printf("q0 --e--> q1\n");
        printf("q1 --e--> q2\n");
        printf("q1 --a--> q1\n");
        printf("q2 --b--> q2\n");
    } else {
        printf("\nEnter total number of states (e.g. 3 for q0, q1, q2): ");
        scanf("%d", &numStates);

        printf("Enter total number of transitions: ");
        scanf("%d", &numTransitions);

        printf("Enter transitions (format: <from_state_int> <symbol> <to_state_int>)\n");
        printf("Use 'e' for epsilon transition. Example: 0 e 1\n");
        for (int i = 0; i < numTransitions; i++) {
            printf("Transition %d: ", i + 1);
            scanf("%d %c %d", &transitions[i].from, &transitions[i].symbol, &transitions[i].to);
        }
    }

    computeAllClosures();
    printClosures();

    return 0;
}
