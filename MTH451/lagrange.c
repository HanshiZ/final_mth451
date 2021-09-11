#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const double pi = 4 * tan(1.0);
double lagrange(double val, double * x, double * y, int n);

int main() 
{
    
    double a[] = {0.0,1};
    double b[] = {0.0,1.0};
    lagrange(2,a,b,1);
    return 0;
}



double lagrange(double val, double * x, double * y, int n)
{
    double ** ptrs = (double **) calloc(n+1, sizeof(double*));
    for(int i = 0; i <= n; ++i)
    {
        printf("L%d : ", i);
        double * lst = (double *) calloc(n+1, sizeof(double));
        double prd = 1; 
        int place = 1;
        for (int j = 0; j <= n; ++j)
        {
            if (i!=j)
            {
                prd = prd * (x[i] - x[j]);
                lst[place] = x[j];
                ++place;
            }
        }
        lst[0] = 1.0/prd;
        for (int k = 0; k <= n; ++k)
        {
            if (k) printf("(x - %.3f)", lst[k]);
            else printf("%.3f", lst[k]);
        }
        ptrs[i] = lst;
        printf("\n");
    }
    double sum = 0;
    for(int a = 0; a <= n; ++a)
    {
        double prod = y[a];
        for(int b = 0; b <= n; ++b)
        {
            if (b) prod = prod*(val - ptrs[a][b]);
            else prod = prod * ptrs[a][b];
        }
        sum = sum + prod;
    }
    for(int c = 0; c<=n ;++c)
    {
        free(ptrs[c]);
    }
    free(ptrs);
    printf("f(%.3f) = %.5f \n",val,sum);
    return sum;
}