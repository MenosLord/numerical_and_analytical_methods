#include <iostream>
#include <cmath>

using namespace std;

double f(double x) 
{
	return (x + cos(pow(x, 0.52) + 2));
}

double df(double x)
{
	return (1 - sin(pow(x, 0.52) + 2) * (0.52 / pow(x, 0.48)));
}

int main()
{
	double eps = 0.0001;
	double a = 0.5;
	double b = 1.0;
	double x0 = 0.55; // стартовая точка
	double x, xn = x0;
	int cnt = 1;
	
	do
	{
		x = xn;
		xn = x - f(x) / df(x);
		cnt++;
		//cout << cnt << "\t" << xn << endl;
	}
	while(fabs(xn - x) > eps);

	cout.precision(5);
	cout << endl << "X:\t" << xn << endl << "Iterations:\t" << cnt << endl << "Error:\t" << fabs(xn - x) << endl;
	
	cin.get();
	return 0;
}