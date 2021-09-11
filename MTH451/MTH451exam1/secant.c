#include <stdio.h>
#include <math.h>
double secant(double p0, double p1,double er, int n, double (*f)(double));
double zerodenom(void);
double f1(double);


const double PI = 4 * atan(1.0);

int main()
{
      
    secant(3,5, .00001,12, (*f1));
    return 0;
}

double secant(double p0, double p1 , double er, int n, double (*f)(double))
{
     double q0 = (*f)(p0);
     double q1 =(*f)(p1);
     
     for(int i = 0; i < n; )
     { 
          ++i;

          printf("Iteration %d, $p_%d$ = %.3f, $p_%d$ = %.3f , $f(p_%d)$ = %.3f , $f(p_%d)$ = %.3f \n",i, i-1 ,p0,i ,p1 ,i-1,q0,i,q1);
          double p = (q1-q0) ? (p1 - q1*(p1-p0)/(q1-q0) ) : zerodenom();
          printf("p:%.6f\n", p);
          if (fabs(f(p)) < er)
          {
              printf("Zero found.\n");
              return p;   
          }
          p0 = p1;    
          p1 = p;
          q0 = q1;
          q1 = f(p);
     }
     printf("Method failed.\n");
     return 0;
}

double zerodenom(void)
{
    printf("Divide by zero method failed.\n");
    return 0;
}

double f1(double x)
{
    return exp(x) - 3*x*x;
}
