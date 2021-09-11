#include <stdio.h>
#include <math.h>

const double PI = 4 * atan(1.0);

double fixed(double p0, double prec, int it, double (*f)(double));
double f1 (double x);

int main()
{
   //fixed(1.5,.01,10,f1);
   //fixed(1,.00001, 4, aiv);
   //fixed(1,.00001, 4, aiii);
   fixed(0, .00001, 20, f1);

   return 0;
}


double fixed(double p0, double prec, int it, double (*f)(double x))
{
     for(int i = 0; i < it; )
     {   
         double point = (*f)(p0); 
         
         printf("Iteration %d: $p_%d$ = %.6f p = %.6f\n" , i+1, i, p0, point);
         ++i;
         if (fabs(point-p0) < prec)
         {
               printf("Point with enough precision found.\n");
               return p0;
         }
         else
               p0 = point;
     }
     return 0;
}

double f1 (double x)
{
    return .5*(sin(x) + cos(x));
}