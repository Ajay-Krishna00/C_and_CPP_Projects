#include<iostream>
using namespace std;
int main ()
{
    int r,s,j,n,t;
    printf("enter the no of rows\n");
    scanf("%d",&n);
    
    for(r=0 ; r<n; r++)    //rows
    {
        for(s=0; s<(n-r-1);s++)printf(" ");     //spaces
        for(j=0; j<2*r+1; j++)printf("*");     // *
        printf("\n");
    }

    for(t=0; t<(n/2); t++)
    {
        for(s=0; s<(n-2);s++)printf(" ");       //spaces
        printf("| |\n");     //wood
    }
    return 0;
}