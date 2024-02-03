//program for Floyd's Triangle
#include <iostream>
using namespace std;
int main()
{
    int i,j,n,count;
    cout<<"Enter the nunmber of rows\t";
    cin>>n;
    count = 1;
    for (i=1; i<=n; i++){  
        for(j=1; j<=i; j++){
            cout<<count<<" ";
            count++;     //this is for printing continuous numbers
            if(j==i){
                cout<<"\n";  
            }
        }
    }
} 