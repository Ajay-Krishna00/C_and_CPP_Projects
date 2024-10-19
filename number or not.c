#include <stdio.h>
#include <ctype.h>
int main(){
    char a;
    printf("enter a number \n");
    scanf("%c", &a);
    if(isdigit(a)){printf("is digit \n");}
    else{printf("not a digit \n");}
    return 0;
}
