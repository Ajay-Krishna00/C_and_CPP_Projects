#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

// List of C keywords to recognize
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
    "main"
};
const int NUM_KEYWORDS = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(const char *str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '!' || ch == '&' ||
            ch == '|' || ch == '^');
}

int isSpecialChar(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']');
}

void analyzeSource(const char *source) {
    int i = 0;
    int line = 1;
    char token[MAX_TOKEN_LEN];

    printf("\n%-10s %-20s %-20s\n", "Line", "Token", "Type");
    printf("------------------------------------------------------\n");

    while (source[i] != '\0') {
        char ch = source[i];

        // 1. Ignore redundant whitespace, tabs, and track newlines
        if (ch == ' ' || ch == '\t') {
            i++;
            continue;
        }
        if (ch == '\n') {
            line++;
            i++;
            continue;
        }

        // 2. Ignore single-line comments
        if (ch == '/' && source[i + 1] == '/') {
            i += 2;
            while (source[i] != '\0' && source[i] != '\n') {
                i++;
            }
            continue;
        }

        // 3. Ignore multi-line comments
        if (ch == '/' && source[i + 1] == '*') {
            i += 2;
            while (source[i] != '\0' && !(source[i] == '*' && source[i + 1] == '/')) {
                if (source[i] == '\n') line++;
                i++;
            }
            if (source[i] != '\0') i += 2;
            continue;
        }

        // 4. Identifiers and Keywords (begins with letter or '_')
        if (isalpha(ch) || ch == '_') {
            int len = 0;
            while ((isalnum(source[i]) || source[i] == '_') && len < MAX_TOKEN_LEN - 1) {
                token[len++] = source[i++];
            }
            token[len] = '\0';

            if (isKeyword(token)) {
                printf("%-10d %-20s %-20s\n", line, token, "Keyword");
            } else {
                printf("%-10d %-20s %-20s\n", line, token, "Identifier");
            }
            continue;
        }

        // 5. Constants / Numbers (Integer and Floating point)
        if (isdigit(ch)) {
            int len = 0;
            int hasDot = 0;
            while ((isdigit(source[i]) || (source[i] == '.' && !hasDot)) && len < MAX_TOKEN_LEN - 1) {
                if (source[i] == '.') hasDot = 1;
                token[len++] = source[i++];
            }
            token[len] = '\0';
            printf("%-10d %-20s %-20s\n", line, token, "Constant (Number)");
            continue;
        }

        // 6. String Literals
        if (ch == '"') {
            int len = 0;
            token[len++] = source[i++];
            while (source[i] != '\0' && source[i] != '"' && len < MAX_TOKEN_LEN - 2) {
                token[len++] = source[i++];
            }
            if (source[i] == '"') token[len++] = source[i++];
            token[len] = '\0';
            printf("%-10d %-20s %-20s\n", line, token, "String Literal");
            continue;
        }

        // 7. Operators (including two-character operators: ==, !=, <=, >=, ++, --, +=, etc.)
        if (isOperator(ch)) {
            int len = 0;
            token[len++] = source[i++];
            if (isOperator(source[i])) {
                token[len++] = source[i++];
            }
            token[len] = '\0';
            printf("%-10d %-20s %-20s\n", line, token, "Operator");
            continue;
        }

        // 8. Delimiters / Special Characters
        if (isSpecialChar(ch)) {
            token[0] = ch;
            token[1] = '\0';
            i++;
            printf("%-10d %-20s %-20s\n", line, token, "Special Character");
            continue;
        }

        // 9. Unknown symbol
        token[0] = ch;
        token[1] = '\0';
        printf("%-10d %-20s %-20s\n", line, token, "Unknown / Error");
        i++;
    }
}

int main() {
    printf("======================================================\n");
    printf("         LEXICAL ANALYZER (CYCLE I - C)               \n");
    printf("======================================================\n");

    const char *sampleCode =
        "int main() {\n"
        "    // Simple calculation\n"
        "    int a = 10;\n"
        "    float b = 20.5;\n"
        "    if (a <= b) {\n"
        "        b = b + a;\n"
        "    }\n"
        "    return 0;\n"
        "}\n";

    printf("1. Run analyzer on built-in sample C code\n");
    printf("2. Enter custom input string\n");
    printf("Enter choice (1 or 2): ");

    int choice = 1;
    if (scanf("%d", &choice) != 1) choice = 1;
    while (getchar() != '\n'); // clear buffer

    if (choice == 2) {
        printf("\nEnter C code (end with a line containing only 'END'):\n");
        char buffer[4096];
        char line[256];
        buffer[0] = '\0';

        while (fgets(line, sizeof(line), stdin)) {
            if (strncmp(line, "END", 3) == 0 && (line[3] == '\n' || line[3] == '\r' || line[3] == '\0')) {
                break;
            }
            strcat(buffer, line);
        }
        analyzeSource(buffer);
    } else {
        printf("\n--- Analyzing Sample Code ---\n%s\n", sampleCode);
        analyzeSource(sampleCode);
    }

    return 0;
}
