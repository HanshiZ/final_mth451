#include <iostream>
#include <cmath>
#include <cstdio>

namespace cmplx
{
    class value;
    value sqrt(const double &d);
    value muller(double p0, double p1, double p2, double er, int it, value (*f)(value));
class value
{
    friend std::ostream &operator <<(std::ostream &o, const value &v)
    {
         o << v.n << "+" << v.i <<"i\n";
         return o;
    } 
    friend double norm(const value &v) {return std::sqrt(v.n*v.n + v.i*v.i);}
    friend value bar(const value &v) {return value(v.n, -1.0 * v.i);}
    friend value sqrt(const value &v, value * vptr = 0) 
    {
         if (!v.i) { return cmplx::sqrt(v.n); } 
         else
         {
             value ret;
             ret.n = std::sqrt(.5*(v.n + norm(v)));
             ret.i = v.i / (2*ret.n);
             if (vptr) {vptr[0] = ret; vptr[1] = -1.0 * ret;}     
             return ret;
         }
    }
    friend value operator+ (const double &d, const value &v) {return value(v.n + d, v.i);}
    friend value operator- (const double &d, const value &v) {return value(d - v.n, 0 - v.i);}
    friend value operator* (const double &d, const value &v) {return value(v.n * d, v.i * d);}
    friend value operator/ (const double &d, const value &v) 
    {
         return ((1.0/(v.n * v.n + v.i * v.i)) * d * bar(v)) ;
    }
    public:
         value(double real = 0, double imag = 0) {n = real; i = imag;}
         value operator+ (const value &v) {return value(n + v.n, i + v.i);}
         value operator- (const value &v) {return value(n - v.n, i - v.i);}
         value operator* (const value &v) {return value(n * v.n - i * v.i, v.i * n + v.n * i);}
         value operator/ (const value &v) 
         {
            double denom = 1.0 / ((v.n * v.n + v.i * v.i));
            value val = value(n * v.n + i * v.i, v.n * i - v.i * n);
            return denom * val;
         }
         void print(void) {printf("%.5f + %.5f i \n",n,i);}

         
    private:
        double n;
        double i;
};

value sqrt(const double &d) {return d < 0 ? value(0, std::sqrt(d)) : value(std::sqrt(d));}

value muller(double p0, double p1, double p2, double er, int it, value (*f)(value))
{
    value i0 = value(p0);
    value i1 = value(p1);
    value i2 = value(p2);
    value h1 = i1 - i0;
    value h2 = i2- i1;
    value d1 = (f(i1) - f(i0)) / h1;
    value d2 = (f(i2) - f(i1)) / h2;
    value d = (d2-d2)/(h1+h2);
    for(int i = 0; i < it; ++i)
    {
        value b = d2 + h2*d;
        value D = sqrt(b*b - 4 * f(p2) * d);
        value E;
        if (norm(b - D) < norm(b+D))
            E = b + D;
        else
            E = b -D;
        value h = -2 * f(p2) / E;
        value p = i2 + h;
        std:: cout << "Iteration " << i + 1 << " : " << p << std::endl;
        if (norm(h) < er)
        {
            std:: cout << "Solution found.\n";
            return p;
        }
        i0 = i1;
        i1 = i2;
        i2 = p;
        h1 = i1 - i0;
        h2 = i2 - i1;
        d1 = (f(i1) - f(i0)) / h1;
        d2 = (f(i2) - f(i1)) / h2;
        d = (d2-d2)/(h1+h2);
        
        
    }
    std:: cout << "This method failed.\n";
    return value(0,0);
}
};


using namespace cmplx;
value f1(value x);
value f2(value x);
value t( value x);
int main()
{
    muller(.5,1,1.5,.0001,20,f2);
    return 0;
}

value f2(value x) {return x*x*x - x -1;}
value t( value x) {return x*x*x*x - 3*x*x*x + x*x + x +1;}
value f1(value x) {return 600*x*x*x*x - 550*x*x*x +200*x*x -20*x -1;}

