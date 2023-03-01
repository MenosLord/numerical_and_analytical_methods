#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y)
{
	return ((y / x) + (1.0 / log(x)));
	//0return (x*(x*x+1)-x*y)/(x*x+1);
    // return (x * log(x) + y / (x * log(x)));
}

double phi(double x)
{
	return (x * log(log(x)));
     //return (0.5 * x * x * log(x));
}

int main() 
{

	double a = exp(1.0); 
	double b = exp(1.0) + 1.0; 
	double h = 0.1;
	double k1 = 0.0;
	double k2 = 0.0;
	double k3 = 0.0;
	double k4 = 0.0;
    int n = floor((b - a) / h) + 1;
    double * x = new double[n]; 
	double * y = new double[n];
    x[0] = exp(1.0); 
	y[0] = 0.0;


	for(int i = 1; i < n; i++)
	{
		x[i] = a + i * h;
		k1 = f(x[i-1], y[i-1]);
		k2 = f(x[i-1] + h / 4.0, y[i-1] + k1 * h / 4.0);
		k3 = f(x[i-1] + h / 4.0, y[i-1] + k2 * h/ 4.0);
		k4 = f(x[i-1] + h, y[i-1] + k3 * h);
		y[i] = y[i-1] + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
	}
    
	for(int i = 0; i < n; i++)
	{
		cout << "x[" << i << "]=" << x[i] << "\t" << "y[" << i << "]=" << y[i] << "\tF[" << i << "]=" << (phi(x[i])) << "\tError = " << fabs(phi(x[i]) - y[i]) << endl;
	}
	
	delete [] x;
	delete [] y;

	cin.get();
	return 0;
}