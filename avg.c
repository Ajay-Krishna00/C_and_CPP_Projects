//#include<stdio.h>
//#include<math.h>
//int main()
//{
// int a,b,c,sum;
// printf("enter three no.");
// scanf("%d", &a);
// scanf("%d", &b);
// scanf("%d", &c);
// sum=a + b + c;
// float avg= (float)sum/3;
// printf("avg is %f",avg );
// return 0;  
// }

#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c, sum;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);
    sum = a + b + c;
    float avg = (float)sum / 3;
    printf("Average is %f", avg);
    return 0;
}
