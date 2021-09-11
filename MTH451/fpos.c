#include <stdio.h>
#include <math.h>
double fpos(double p0, double p1,double er, int n, double (*f)(double));
double zerodenom(void);
double f1(double);
double a12(double x);
double b12(double x);

const double PI = 4 * atan(1.0);

int main()
{
      
    fpos(.5,1, .0000001, 100, (*b12));
    return 0;
}

double fpos(double p0, double p1 , double er, int n, double (*f)(double))
{
     double q0 = (*f)(p0);
     double q1 =(*f)(p1);
     
     for(int i = 0; i < n; )
     { 
          ++i;

          printf("Iteration %d, p0 = %.5f, p1 = %.5f , f(p0) = %.3f , f(p1) = %.3f\n",i, p0, p1 ,q0,q1);
          double p = (q1-q0) ? (p1 - q1*(p1-p0)/(q1-q0) ) : zerodenom();
          printf("p:%.9f\n", p);
          if (fabs(p- p1) < er)
          {
              printf("Zero found.\n");
              return p;   
          }
          if (f(p)*q1 < 0)
          {   
               p0 = p1;    
               q0 = q1;
          }
          p1 = p;
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
    return cos(x)- x;
}

double a12(double x)
{
    return x*x - 4*x + 4 - log(x);
}
double b12(double x)
{
    return x + 1 - 2*sin(PI*x);
}