//Program to sort elements of an array using Bubble sort in Ascending order
#include <stdio.h>
int main(){
    int n,i,j,temp;
    printf("enter the no. of elements");
    scanf("%d",&n);
    int arr[50];
    for(i=0; i<n; i++){
        scanf("%d",&arr[i]);    
    }
    for (i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }
    for(i=0; i<n; i++){
        printf("%d",arr[i]);
    }
    return 0;
}
