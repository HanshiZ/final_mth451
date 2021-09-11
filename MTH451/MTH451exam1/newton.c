#include <stdio.h>
#include <math.h>
double newton(double p0, double er, int n, double (*f)(double) , double (*d)(double));
double zerodenom(void);

double f1(double x);
double d1(double x);

int main()
{
    
    newton(.5,.00001,20, f1,d1);

    return 0;
}

double newton(double p0, double er, int n, double (*f)(double) , double (*d)(double))
{
     
     for(int i = 0; i < n; )
     { 
          ++i;
          printf("Iteration %d, $p_%d$ = %.6f, f($p_%d$) = %.6f\n",i,i-1, p0,i-1, (*f)(p0));
          if (fabs((*f)(p0)) < er)
          {
              printf("Zero found.\n");
              return p0;   
          }    
          p0 = (*d)(p0) ? (p0 - (*f)(p0) / (*d)(p0)) : zerodenom();
     }
     printf("Method failed.\n");
     return 0;
}

double zerodenom(void)
{
    printf("Divide by zero method failed.\n");
    return 0;
}

double f1(double x) {return exp(x) - 3*x*x ;}

double d1(double x) {return exp(x) - 6*x ;}
