%{
#include <stdio.h>
#include <string.h>

/*
 * Cycle II - Program 1
 * Lex program to recognize all strings which DO NOT contain
 * the first four characters of your name as a substring.
 *
 * Author: Ajay Krishna -> First 4 characters: "AJAY"
 */

int contains_sub = 0;
%}

%option noyywrap

%%

[aA][jJ][aA][yY]    { contains_sub = 1; }

\n {
    if (contains_sub) {
        printf(" -> REJECTED: Contains substring 'AJAY'\n");
    } else {
        printf(" -> ACCEPTED: Does NOT contain substring 'AJAY'\n");
    }
    contains_sub = 0;
    printf("\nEnter a string (Ctrl+C or Ctrl+Z to stop): ");
}

. { /* match any other character */ }

%%

int main() {
    printf("======================================================\n");
    printf("   LEX: STRINGS WITHOUT FIRST 4 CHARACTERS OF NAME    \n");
    printf("   Target substring: 'AJAY' (case-insensitive)        \n");
    printf("======================================================\n");
    printf("Enter a string (Ctrl+C or Ctrl+Z to stop): ");
    yylex();
    return 0;
}
