#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y)
{
	//return (x * log(x) + y / (x * log(x)));
	return ((x-1.0)/x*x)*y;
}

double phi(double x)
{
	//return (0.5 * x * x * log(x));
	return x*exp(1.0/x);
}

double integralT(double a, double b, double y)
{
	double dx = 0.000001;
	double s = 0.5 * (f(a, y) + f(b, y));
	double x = a;
	int n = int((b - a) / dx);
	for (int i = 1; i < (n - 1); ++i)
	{
		x += dx;
		s += f(x, y);
	}
	return (s * dx);
}

double integralS(double a, double b, double y)
{
	int n = 4, i = 0, k = 1;
	double I1 = 0.0, I2 = 0.0, h = (b - a) / n;
	double x0, x1, x2, s = 0.0;
	double eps = 0.001;

	do
	{
		I1 = I2;
		I2 = 0.0;
		n *= 2;
		h /= 2;
		i = 0;
		while (i < n)
		{
			i += 2;
			x2 = a + i * h;
			x1 = x2 - h;
			x0 = x1 - h;
			s = f(x0, y) + 4 * f(x1, y) + f(x2, y);
			I2 += s;
		}
		I2 *= (h / 3);
	}while (abs(I1 - I2) > eps);

	return I2;
}

int main()
{
	double a = 1.0;
	double b = 2.0;
	double h = 0.1;
	//cout << integralT(0, 1, 0);
	int n = int((b - a) / h);
	double * x = new double[n + 1];
	double * y = new double[n + 1];
	x[0] = 1.0;
	y[0] = exp(1.0);
	for (int i = 1; i <= n; ++i)
	{
		x[i] = a + i * h;
		y[i] = y[i - 1] + integralS(x[i - 1], x[i], y[i - 1]);
	}

	for (int i = 0; i <= n; ++i)
		cout << "X[" << i << "] = " << x[i] << "\tY[" << i << "] = " << y[i] << "\tF[" << i << "] = " << phi(x[i]) << "\tError = " << fabs(y[i] - phi(x[i]))<< endl;
	
	cin.get();
	return 0;
}