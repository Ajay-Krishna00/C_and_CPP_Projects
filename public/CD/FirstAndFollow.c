#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 50
#define MAX_LEN 50

typedef struct {
    char lhs;
    char rhs[MAX_LEN];
} Production;

int numProd = 0;
Production prods[MAX_PROD];

char nonTerminals[26];
int numNT = 0;

void addNonTerminal(char nt) {
    for (int i = 0; i < numNT; i++) {
        if (nonTerminals[i] == nt) return;
    }
    nonTerminals[numNT++] = nt;
}

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

void addToSet(char *set, char val) {
    if (strchr(set, val) == NULL) {
        int len = strlen(set);
        set[len] = val;
        set[len + 1] = '\0';
    }
}

// Compute FIRST of a symbol (or string)
void findFirst(char symbol, char *firstSet) {
    // If terminal or epsilon ('#' or 'e')
    if (!isNonTerminal(symbol)) {
        addToSet(firstSet, symbol);
        return;
    }

    for (int i = 0; i < numProd; i++) {
        if (prods[i].lhs == symbol) {
            // Epsilon production
            if (prods[i].rhs[0] == '#' || prods[i].rhs[0] == 'e') {
                addToSet(firstSet, '#');
            } else {
                for (int j = 0; prods[i].rhs[j] != '\0'; j++) {
                    char nextSymbol = prods[i].rhs[j];
                    char subFirst[MAX_LEN] = "";
                    findFirst(nextSymbol, subFirst);

                    // Add all except epsilon
                    for (int k = 0; subFirst[k] != '\0'; k++) {
                        if (subFirst[k] != '#') {
                            addToSet(firstSet, subFirst[k]);
                        }
                    }

                    // If subFirst doesn't contain epsilon, stop
                    if (strchr(subFirst, '#') == NULL) {
                        break;
                    }

                    // If reached end and all produced epsilon, add epsilon
                    if (prods[i].rhs[j + 1] == '\0') {
                        addToSet(firstSet, '#');
                    }
                }
            }
        }
    }
}

// Compute FOLLOW of a non-terminal
void findFollow(char symbol, char *followSet, int visited[]) {
    int ntIdx = symbol - 'A';
    if (visited[ntIdx]) return;
    visited[ntIdx] = 1;

    // Start symbol gets '$'
    if (symbol == prods[0].lhs) {
        addToSet(followSet, '$');
    }

    for (int i = 0; i < numProd; i++) {
        int rhsLen = strlen(prods[i].rhs);
        for (int j = 0; j < rhsLen; j++) {
            if (prods[i].rhs[j] == symbol) {
                // Look at symbols following 'symbol' in this production
                int k = j + 1;
                while (k < rhsLen) {
                    char nextSym = prods[i].rhs[k];
                    char nextFirst[MAX_LEN] = "";
                    findFirst(nextSym, nextFirst);

                    for (int m = 0; nextFirst[m] != '\0'; m++) {
                        if (nextFirst[m] != '#') {
                            addToSet(followSet, nextFirst[m]);
                        }
                    }

                    if (strchr(nextFirst, '#') == NULL) {
                        break; // Does not derive epsilon
                    }
                    k++;
                }

                // If symbol is at the end or all trailing symbols derive epsilon
                if (k == rhsLen && prods[i].lhs != symbol) {
                    int subVisited[26] = {0};
                    findFollow(prods[i].lhs, followSet, subVisited);
                }
            }
        }
    }
}

void printSet(const char *set) {
    printf("{ ");
    int len = strlen(set);
    for (int i = 0; i < len; i++) {
        if (set[i] == '#') {
            printf("e");
        } else {
            printf("%c", set[i]);
        }
        if (i < len - 1) printf(", ");
    }
    printf(" }");
}

int main() {
    printf("======================================================\n");
    printf("       SIMULATION OF FIRST AND FOLLOW (CYCLE III)     \n");
    printf("   Use '#' for epsilon (e), Capital letters for NT   \n");
    printf("======================================================\n");

    printf("1. Run with standard textbook expression grammar:\n");
    printf("   E -> TR\n   R -> +TR | #\n   T -> FY\n   Y -> *FY | #\n   F -> (E) | i\n");
    printf("2. Enter custom grammar\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;

    if (choice == 1) {
        numProd = 8;
        prods[0] = (Production){'E', "TR"};
        prods[1] = (Production){'R', "+TR"};
        prods[2] = (Production){'R', "#"};
        prods[3] = (Production){'T', "FY"};
        prods[4] = (Production){'Y', "*FY"};
        prods[5] = (Production){'Y', "#"};
        prods[6] = (Production){'F', "(E)"};
        prods[7] = (Production){'F', "i"};

        for (int i = 0; i < numProd; i++) {
            addNonTerminal(prods[i].lhs);
        }
    } else {
        printf("Enter number of productions: ");
        scanf("%d", &numProd);

        printf("Enter productions (format: LHS RHS, e.g., E TR or R # for epsilon):\n");
        for (int i = 0; i < numProd; i++) {
            char lhs[10], rhs[50];
            printf("Prod %d: ", i + 1);
            scanf("%s %s", lhs, rhs);
            prods[i].lhs = lhs[0];
            strcpy(prods[i].rhs, rhs);
            addNonTerminal(prods[i].lhs);
        }
    }

    printf("\n------------------------------------------------------\n");
    printf("%-15s %-25s %-25s\n", "Non-Terminal", "FIRST", "FOLLOW");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < numNT; i++) {
        char nt = nonTerminals[i];
        char firstSet[MAX_LEN] = "";
        char followSet[MAX_LEN] = "";
        int visited[26] = {0};

        findFirst(nt, firstSet);
        findFollow(nt, followSet, visited);

        printf("%-15c ", nt);
        printSet(firstSet);
        printf("%*s", (int)(25 - (strlen(firstSet) * 3)), "");
        printSet(followSet);
        printf("\n");
    }
    printf("------------------------------------------------------\n");

    return 0;
}
