#include <stdio.h>
#include <math.h>
#define MAX 100
double simpson(double a, double b, int iter, double (*f)(double));

double trapezoid(double a, double b, int iter , double (*f)(double));

double adaptsimpson(double a, double b, int level, double tol, double (*f) (double));
double t(double x);
double f(double x);
double g(double x);
int main()
{
    //printf("Final estimate: %.10f",adaptsimpson(.1,2,0,.001,t));
    printf("Final result: %.7f", /*simpson(1,3,6,g)*/ trapezoid(1,3,46,g));
    return 0;
}

double g(double x)
{
    return 1.0 / (x + 3);
}

double simpson(double a, double b, int iter, double (*f)(double))
{
    double leng =  (b - a) / iter;
    double integral = 0;
    for( int i = 0; i < iter; ++i)
    {
        double x = (leng / 6) * 
        (f(i * leng + a) + 
        4*f((i+.5) * leng + a) +
        f((i+1)*leng + a));
        printf("Simpson on [%.3f, %.3f] = %.5f \n",i * leng + a,(i+1)*leng + a ,x);
        
        integral = integral + x;
    }
    return integral;
}

double trapezoid(double a, double b, int iter , double (*f)(double))
{
    double leng =  (b - a) / iter;
    double integral = 0;
    for( int i = 0; i < iter; ++i)
    {    
        double x = (f(a + i * leng) + f(a+(i+1)*leng)) * leng / 2;
        integral = integral + x;
        if (!i || i > iter - 3)
            printf("Trapezoid %d on [%.3f, %.3f]: %.5f\n",i+1,a + i * leng, a+(i+1)*leng, x);
    }
    return integral;
}

double f(double x)
{
    return exp(x);
}

double adaptsimpson(double a, double b, int level, double tol, double (*f) (double))
{
    if (level == MAX) {printf("Failed.\n"); return 0;}
    double val = simpson(a,b,1,f);
    double check = simpson(a,b,2,f);
    double dif = val - check;
    if (fabs(dif) < 10 * tol)
    {
        printf("Simpson on %.3f, %.3f : %.5f \n Simpson on interval divided in half : %.5f \n", a,b, val, check);
        printf("Difference, tolerance * 10: %.5f, %.5f \n", dif, tol * 10);
    
        return check;
    }
    else
    {
        double half = a + (b-a)/2;
        return adaptsimpson(a,half,level+1,.5*tol,f) + adaptsimpson(half,b,level+1,.5*tol,f);
    }
}

double t(double x)
{
    return (sin(1.0/x));
}
