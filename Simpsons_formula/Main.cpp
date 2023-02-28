#include <iostream>
#include <cmath>

using namespace std;

double y(double x)
{
	//return (1 / (x *log10(x)));
	//return tan(x)*tan(x)+(1/(tan(x)*tan(x)));
	//return 1/(sqrt(1+3*x+2*x*x));
	return (log(x))/(x*(sqrt(1+log(x))));
}
double g (double x)
{
	return  (2.0/3.0)*pow((log(x)+1.0),3.0/2.0) - 2.0* pow((log(x)+1.0), 1.0/2.0) +(4.0/3.0);
}
int main()
{
	double a = 1;
	double b = 3.5;
	double eps = 0.001;


	int n = 4, i = 0, k = 1;
	double I1 = 0.0, I2 = 0.0, h = (b - a) / n;
	double x0, x1, x2, s = 0.0;

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
			s = y(x0) + 4 * y(x1) + y(x2);
			I2 += s;
		}
		I2 *= (h / 3);
		cout << "Iteration: " << k++ << ";\t" << "Integral: " << I2 << endl;
	}while (abs(I1 - I2) > eps);

	cout << endl << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "eps = " << eps << endl;
	cout << endl << "I = " << I2 << endl;
	cout << "g(b)= " << g(b) << endl;
	cout << "g(a)= " << g(a) << endl;
	cout << abs(I2 - g(b)+g(a))<< endl;
	cout << "G= " << (g(b)-g(a)) << endl;
	cin.get();
	cin.get();
	return 0;
}