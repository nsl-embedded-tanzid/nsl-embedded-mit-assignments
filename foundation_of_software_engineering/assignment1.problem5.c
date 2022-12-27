#include<stdio.h>

void time_clock(int n)
{
    if(n == 1 || n%2 == 0)
        return;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==0 || j==i || j==n-i-1 || i==n-1)
                printf("*");
            else
                printf(" ");
        } 
        printf("\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    time_clock(n);

    return 0;
}