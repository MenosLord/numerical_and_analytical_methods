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

double best_lambda(double a, double b)
{
	double tmp = 0.0;
	double h = 0.1;
	double x = a;
	double bst = fabs(df(x));
	int n = int((b - a) / h);
	for(int i = 0; i < n; i++)
	{
		x += h;
		tmp = fabs(df(x));
		//cout << x << "\t" << tmp << endl;
		if (tmp > bst)
			bst = tmp;
	}
	return (1.0 / bst);
}

int main()
{
	double eps = 0.0001;
	double a = 0.5;
	double b = 1.0;
	double lambda;
	double x0 = 0.55;
	double x, xn = x0;
	int cnt = 1;
	
	lambda = best_lambda(a, b);

	do
	{
		x = xn;
		xn = x - lambda * f(x);
		cnt++;
		//cout << cnt << "\t" << xn << endl;
	}
	while(fabs(xn - x) > eps);

	cout.precision(5);
	cout << "Step:\t" << lambda << endl << "X:\t" << xn << endl << "Iterations:\t" << cnt << endl << "Error:\t" << (xn - x) << endl;
	
	cin.get();
	return 0;
}