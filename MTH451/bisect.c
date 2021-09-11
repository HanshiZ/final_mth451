#include <math.h>
#include <stdio.h>

double f1(double x);
double f2(double);

double f7(double);
double f9(double);
double f14(double x);

double bisection(double lower, double upper, double prec, int it, double (*f)(double x));

int main()
{
    /*printf("Zero : %.5f\n", bisection(0.0, 1.0, .00001, 3, f2));
    printf("Zero : %.5f\n", bisection(3, 1.5, 0.00001, 20, f7));
    
    printf("Zero : %.7f\n", bisection(1.5, .5, 0.00001, 20, f9));*/
    printf("Zero : %.7f\n", bisection(1, 4, 0.001, 13, f14));
    return 0;
}

double bisection(double lower, double upper, double prec, int it, double (*f)(double x))
{
     if ((*f)(lower) > 0 || (*f)(upper) < 0)
     {   printf("Invalid input bounds.\n");      
         return 0;
     }
     for(int i = 0; i < it; )
     {      
         printf("Iteration %d: upper = %.5f , lower = %.5f \n" , ++i, upper, lower);
         double mid = .5*(upper + lower);
         double fm = (*f)(mid);
         printf("New mid point %.5f and f(mid) %.7f .\n", mid, fm);
         if (fm > -prec && fm < prec)
         {
               printf("Zero with enough precision found.\n");
               return mid;
         }
         else if (fm < 0)
              lower = mid;
         else 
              upper = mid;         
     }
     return 0;
}

double f1(double x)
{
     return log(x);     
}

double f2(double x)
{
    return sqrt(x) - cos(x);
}

double f7(double x)
{
    return 2 * sin(x) - x;   
}

double f9(double x)
{
    return cos(exp(x)-2)+2 - exp(x);
}

double f14(double x)
{
    return x*x*x + x - 4;
}