#include <iostream>
#include <cmath>
using namespace std;

double y(double x)
{
	//return (1 / (x *log10(x)));
	//return tan(x)*tan(x)+(1/(tan(x)*tan(x)));
	//return  (x * atan(x))/(sqrt(1+x*x));
	return x* pow(2.7182818,x) * sin(x);
}
double g (double x)
{
	//return sqrt(1+x*x) * atan(x)-log(x+sqrt(1+x*x));
	return (x* pow(2.7182818,x)*(sin(x)-cos(x))+ pow(2.7182818,x) * cos(x)-1)/2;
}
int main()
{
	int n =48;  
	double a = 0; 
	double b = 1;
	double dx = (b - a) / n;
	double eps = 0.001;
	double s = 0;
	for (int i = 0; i < n; i++)
	{
		s += y(a + (i + 1) * dx) + y(a + i * dx);
	}
	cout << "I= " << (s * dx / 2) << ";\tn= " << n << endl;
	cout << "G= " << (g(b)-g(a)) << endl;
	cout << abs(s*dx/2 - g(b)+g(a))<< " < eps "<< endl;
	
	cin.get();
	cin.get();
	return 0;
}
