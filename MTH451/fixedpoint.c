#include <stdio.h>
#include <math.h>

const double PI = 4 * atan(1.0);

double fixed(double p0, double prec, int it, double (*f)(double));
double f1 (double x);

double ai(double);
double aii(double);
double aiii(double);
double aiv(double);
double f7(double);
double f11b(double);
int main()
{
   //fixed(1.5,.01,10,f1);
   //fixed(1,.00001, 4, aiv);
   //fixed(1,.00001, 4, aiii);
   fixed(2, .01, 20, f7);
   fixed (3, .00001, 100, f11b);
   return 0;
}


double fixed(double p0, double prec, int it, double (*f)(double x))
{
     for(int i = 0; i < it; )
     {   
         double point = (*f)(p0); 
         
         printf("Iteration %d: p%d = %.6f p = %.6f\n" , i+1, i, p0, point);
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
    return sqrt(10 /(4+x));
}

double f7 (double x)
{
   return PI + .5* sin(x/2); 
}

double ai(double x) {return pow(3+x-2*x*x,.25);}

double aii(double x) {return pow(.5*(x+3-pow(x,4)),.5);}

double aiii(double x) {return pow((x+3)/(x*x+2),.5);}

double aiv(double x) {return (x*x*(3*x*x+2) + 3)/(4*x*x*x+4*x-1);}

double f11b(double x)
{
    return 5/(x*x) + 2;
}