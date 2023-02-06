#include <iostream>
#include <thread>
#include <cmath>
#include <mutex>
#include <vector>

using namespace std;

double sum = 0;
mutex mut;

double f(double x)
{
	return 3 * pow(x, 3) + cos(7 * x) - log(2 * x);
}
double Integral(double start, double stop)
{
	double dx = 1.0e-6;
	double x = start;
    
    lock_guard<mutex> m{mut};
    
	while (x < stop)
	{
		sum += f(x) * dx;
		x += dx;
	}
	
	return sum;
}

int main()
{
    vector<thread> threads;
    double p = 1.0;
    double k = 4.9;
    for(int i = 0; i <10; ++i)
    {
        threads.push_back(thread(Integral, p, k ));
        p += 3.9;
        k += 3.9;
    }
    for(thread &t : threads)
    t.join();
    
    cout << "integral = " << sum << "\n";
    return 0;
}