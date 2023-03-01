#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y)
{
        return (y - ((2*x)/y));
}

int main() 
{
	double a = 0.0; 
	double b = 1.0; 
	double h = 0.2;
    int n = floor((b - a) / h) + 1;
    double * x = new double[n]; 
	double * y = new double[n];
    x[0] = a; 
	y[0] = 1;
	for(int i = 1; i < n; i++)
	{
		x[i] = a + i * h;
		y[i] = y[i-1] + h * f(x[i-1], y[i-1]);
	}
    
	for(int i = 0; i < n; i++)
	{
		cout << "x[" << i << "]=" << x[i] << "\t" << "y[" << i << "]=" << y[i] << endl;
	}
	
	delete [] x;
	delete [] y;

	cin.get();
	return 0;
}