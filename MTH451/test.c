#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
unsigned long factorial(unsigned long n);

unsigned long C(unsigned long n, unsigned long r);

unsigned long P(unsigned long n, unsigned long r);

double binpmf(int k, int n, double p);
double bincdf(int k, int n, double p);
int genbin(int, double);

double binCLTnormal(double mean, double var, int n, double p);

void printstat(int n, int *, char);

int main()
{
    srand(time(0));
    int data[20] = {0};
    for(int i = 0; i < 100; ++i)
    {
        int result = floor(binCLTnormal(10,10,105,.5));

        if (result < 0)
            ++data[0];
        else if (result >= 20)
            ++data[19];
        else
            ++data[result];
    }
    printstat(20,data, '*');
    return 0;
}

void printstat(int n, int * data, char symbol)
{
    for(int i = 0; i < n; ++i)
    {
        
        putchar('|');
        for(int j = 0; j < data[i]; ++j)
        {  
            printf("%2d:",data[i]);
            putchar(symbol);
        }
        putchar('\n');
    }
}

double binCLTnormal(double mean, double var, int n, double p)
{
    double dif = genbin(n,p) - n*p;
    double z = dif / sqrt(n * (1-p) * p);
    return z * sqrt(var) + mean;
}

int genbin(int n, double p)
{
    int count = 0;
    for( ; n ;--n)
        count = ((1.0*rand()) / RAND_MAX < p) ? count + 1 : count;
    return count;
}
double binpmf(int k,int n, double p)
{
    return ((double)C(n, k)) *  pow(p,k) * pow(1-p,n-k);
}

double bincdf(int k, int n, double p)
{
    double sum;
    for(;k > -1; --k)
        sum = sum + binpmf(k,n,p);
    return sum;
}

unsigned long factorial(unsigned long n)
{
    unsigned long product = 1;    

    if (!n)    return product;
    
    for (unsigned long i = n; i > 1 ; --i)
       product = product * i;

    return product;
}

/* Permutation n permute r */
unsigned long P(unsigned long n, unsigned long r)
{
    unsigned long prod =1;
    for ( ;r; --n, --r)
        prod = prod * n;
    return prod;
}

/* Combination n pick r */
unsigned long C(unsigned long n, unsigned long r)
{
    r  = (n - r) < r ? n - r : r ;
    if (r)   
    {
        unsigned long prod = 1;
        unsigned long denom = factorial(n-r);
        for (; r < n; --n)
            prod = prod * n;
        prod = prod /  denom;
        return prod;
    }
    else return 1;
}