#include <stdio.h>
#include <math.h>
double newton(double p0, double er, int n, double (*f)(double) , double (*d)(double), double (*dd)(double));
double zerodenom(void);

double f1(double x);
double d1(double x);
double d1d(double);
double d1dd(double);
double a1(double x);
double a1d(double);
double a1dd(double);
double b1(double x);
double b1d(double);
double b1dd(double);
double c1(double x);
double c1d(double);
double c1dd(double);

double d2(double x);
double d2d(double);
double d5(double x);
double d5d(double);
double d5dd(double);
int main()
{
    
    newton(0,.00001,20, c1,c1d,c1dd);
    newton(-2,.00001,20, b1,b1d,b1dd);
    return 0;
}

double newton(double p0, double er, int n, double (*f)(double) , double (*d)(double),double (*dd)(double))
{
     
     for(int i = 0; i < n; )
     { 
          ++i;
          printf("Iteration %d, p = %.6f, f(p) = %.3f\n",i, p0, (*f)(p0));
          if (fabs((*f)(p0)) < er)
          {
              printf("Zero found.\n");
              return p0;   
          }    
          p0 = ((*d)(p0)*(*d)(p0)-(*f)(p0)*(*dd)(p0))? (p0 - (*f)(p0)*(*d)(p0) / ((*d)(p0)*(*d)(p0)-(*f)(p0)*(*dd)(p0))) : zerodenom();
     }
     printf("Method failed.\n");
     return 0;
}

double zerodenom(void)
{
    printf("Divide by zero method failed.\n");
    return 0;
}

double f1(double x) {return -cos(x) + x ;}

double a1(double x) {return (x-exp(-x))*(x-exp(-x));}

double a1d(double x) {return 2*x - (2*exp(-x) - 2*x*exp(-x)) - 2*exp(-2*x);}

double a1dd(double x) {return 2 - (-2*exp(-x) + 2*x*exp(-x) - 2 *exp(-x)) + 4*exp(-2*x);}

double b1(double x){return cos(x+sqrt(2)) + x*x/2 + sqrt(2) * x;}

double b1d(double x){return -sin(x+sqrt(2)) + x + sqrt(2);}

double b1dd(double x){return -cos(x+sqrt(2)) + 1;}

double c1(double x) 
{return x*x*x -3*x*x*exp(-x*log(2)) + 3* x * exp(-x*log(4)) - exp(-x*log(8));}

double c1d(double x) 
{return 3*x*x - 6*x*exp(-x*log(2)) + 3*log(2) *x*x*exp(-x*log(2)) + 3*exp(-x*log(4)) - 3*x*log(4) * exp(-x*log(4)) + log(8) * exp(-x*log(8));}

double c1dd(double x) 
{return 6*x - 6*exp(-x*log(2)) + 6*log(2)*x*exp(-x*log(2)) + 6*log(2) *x*exp(-x*log(2))-3*log(2)*log(2) *x*x*exp(-x*log(2)) - 3*log(4)*exp(-x*log(4)) - 3*log(4) * exp(-x*log(4)) + 3*x*log(4)*log(4)*exp(-x*log(4)) -log(8)*log(8) * exp(-x*log(8));}

double d1(double x) 
{return exp(6*x) + 3* log(2)*log(2)*exp(2*x) -log(8) *exp(4*x)- pow(log(2),3);}

double d1d(double x) 
{return 6*exp(6*x) + 6* log(2)*log(2)*exp(2*x) -4*log(8) *exp(4*x);}

double d1dd(double x) 
{return 36*exp(6*x) + 12 * log(2)*log(2)*exp(2*x) -16*log(8) *exp(4*x);}

double d5(double x) 
{return exp(6*x) + 1.441* exp(2*x) -2.079 *exp(4*x)- .333;}

double d5d(double x) 
{return 6*exp(6*x) + 2* 1.441 * exp(2*x) -4*2.079 *exp(4*x);}

double d5dd(double x) 
{return 36*exp(6*x) + 4* 1.441 * exp(2*x) -16*2.079 *exp(4*x);}





double d2(double x)
{
    return exp(3*x) - 9*x*x*(3*pow(x,4) -3*x*x*exp(x) + exp(2*x));
}

double d2d(double x)
{
    return 3*exp(3*x) - 18*x*(3*pow(x,4) -3*x*x*exp(x) + exp(2*x))
    - 9*x*x*(12*pow(x,3) -3*x*x*exp(x) - 6*x*exp(x) + 2*exp(2*x));
}



