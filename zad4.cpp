#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

double sum = 0;

double f(double x)
{
	return 3 * pow(x, 3) + cos(7 * x) - log(2 * x);
}
double Integral(double start, double stop)
{
	double dx = 1.0e-6;
	double x = start;
    double sum_local = 0;
    
	while (x < stop)
	{
		sum_local += f(x) * dx;
		x += dx;
	}
	
	return sum_local;
}

int main()
{
    double p = 1.0;
    double k = 4.9;
    
    #pragma omp parallel for reduction (+:sum)
    for(int i = 0; i <10; ++i)
    {
        sum += Integral(p, k);
        p += 3.9;
        k += 3.9;
    }
    
    cout << "integral = " << sum << "\n";
    return 0;
}