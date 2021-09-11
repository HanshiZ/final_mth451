#include <math.h>
#include <stdio.h>

double f1(double x);


double bisection(double lower, double upper, double prec, int it, double (*f)(double x));

int main()
{

    printf("Zero : %.7f\n", bisection(1, 4, 0.001,20, f1));
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
         printf("Mid-point %.5f and f(mid) %.5f.\n", mid, fm);
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
     return x*x*x+x-4;     
}
