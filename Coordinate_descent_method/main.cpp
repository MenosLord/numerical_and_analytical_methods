#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y) 
{
	return 2*x*x + y*y*y - 4*x- 3*y +6;
	//return x*x+3*y*y+4*x-6*y+7;
    //return x*x*x+y*y-6*x*y-39*x+18*y+20;
	//return x*x + y*y + x*y - 3*x - 6*y;
	//return x*x*x + 8*y*y*y - 6*x*y + 1;
	//return 7*x*x+2*x*y+5*y*y+x-10*y;
	//return x*x*x+y*y-6*x*y-39*x+18*y+20;
}

double dfx(double x, double y) 
{
	double e = 0.000001;
	return ((f(x + e, y) - f(x, y)) / e);
}

double dfy(double x, double y) 
{
	double e = 0.000001;
	return ((f(x, y + e) - f(x, y)) / e);
}

int main(){
	setlocale(LC_ALL, "Russian");
	double x0, y0, hx = 0.02, hy = 0.02, y = 0.0, x = 0.0, dif1, dif2, eps = 0.01;
	int iter = 0;
	do
	{
		do 
		{
			x0 = x;
			x = x - hx * dfx(x, y);
			dif1 = fabs(dfx(x, y)); //условие остановки вычисл€ет
	//		cout << iter << "\t" << dif << endl;
			iter++;
		} while (dif1 > eps);
		do 
		{
			y0 = y;
			y = y - hy * dfy(x, y);
			dif2 = fabs(dfy(x, y)); //условие остановки вычисл€ет
	//		cout << iter << "\t" << dif << endl;
			iter++;
		} while (dif2 > eps);
	}while((sqrt(dif1*dif1+dif2*dif2))>eps);
	cout << "(x, y) = (" << x << ", " << y << " )" << endl;
	cout << "ќтвет: " << f(x, y) << endl << " ол-во итераций: " << iter << endl;
    cout << "|x-x0| < eps :: " << sqrt(dif1*dif1+dif2*dif2) << " < " << eps << endl;
	cin.get();
	return 0;
}
