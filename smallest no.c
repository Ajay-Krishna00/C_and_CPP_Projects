#include<stdio.h>
int main(){
    printf("enter 2 no. \n");
    int a,b;
    scanf("%d",&a);
    scanf("%d",&b);
    if(a>b){
    printf("smallest number is %d",b);    }else{
    printf("smallest number is %d",a);     }
    return 0;   
}