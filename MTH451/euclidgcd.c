#include <stdio.h>

int euclidgcd(int a, int b);

int main()
{
    euclidgcd(524,128);
    
    return 0;
}


int euclidgcd(int a, int b)
{   
    int max = a > b ? a : b;
    b = max == a ? b : a;        
    do
    {
        a = max % b;
        printf("Dividend %d, divisor %d, remainder %d\n", max, b , a);
        max = b;
        b = a;  
    }
    while (a);

    return  max;
}