#include <stdio.h>
#include <math.h>

double steffensen(double p0, double er,int it,double (*f)(double));
double f1(double);
double f5(double);
double d11(double x);
double c11(double x);
double b11(double x);
double a11(double x);

int main()
{
   steffensen(1.5,0.0001,20,f5);
   return 0;
}

double steffensen(double p0, double er,int it,double (*f)(double))
{
    for(int i = 0; i < it; )
    {
        ++i;
        double p1 = f(p0);
        double p2 = f(p1);
        if (!(p2 - 2*p1 + p0))
        {    printf("Zero denominator.\n");
             break;
        }

        double ret = p0 - (p1-p0)*(p1-p0)/(p2 - 2*p1 + p0);
        printf("Iteration %d: ~%.6f , p012: %.5f, %.5f, %.5f\n", i,ret,p0,p1,p2);
        if (fabs(ret - p0) < er)
        {
             printf("Fixed point");
             return ret;
        }      
        p0 = ret;          

    }
    printf("Method failed.\n");
    return 0;
}

double f1(double x)
{
    return sqrt(10/(x+4));    
}

double f5(double x)
{
    return pow(x+1,1/3.0);
}

double a11(double x)
{
    return (2-exp(x)+ x*x)/3;
}

double b11(double x)
{
    return .5*(cos(x) + sin(x));
}

double c11(double x)
{
    return pow(exp(x)/3,.5);
}

double d11(double x)
{
    return pow(5,-x);
}