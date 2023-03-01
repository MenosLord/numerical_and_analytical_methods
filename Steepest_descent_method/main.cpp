#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y) 
{
	//return 7 * (x * x) + 2 * x * y + 5 * (y * y) + x - 10 * y;
	return 2*x*x + y*y*y - 4*x- 3*y +6;
	//return (x*x+y-11)*(x*x+y-11)+(x+y*y-7)*(x+y*y-7);
	//return x*x*x + 8*y*y*y - 6*x*y + 1;
	//return x*x*x+y*y-6*x*y-39*x+18*y+20;
	//return (x-3)*(x-3)+(y-2)*(y-2)+(x-y-4)*(x-y-4);
	//return x*x+y*y+x*y-3*x-6*y;
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
	double x0, y0, hx = 0.02, hy = 0.02, y = 0.0, x = 0.0, dif, eps = 0.01;
	int iter = 0;

	do {
		x0 = x;
		y0 = y;
		x = x - hx * dfx(x, y);
		y = y - hy * dfy(x, y);
		dif = sqrt(pow(dfx(x, y), 2) + pow(dfy(x, y), 2)); //условие остановки вычисляет
		cout << iter << "\t" << dif << endl;
		iter++;
	} while (dif > eps);
	cout << "(x, y) = (" << x << ", " << y << " )" << endl;
	cout << "Ответ: " << f(x, y) << endl << "Кол-во итераций: " << iter << endl;
    cout << "|x-x0| < eps :: " << dif << " < " << eps << endl;
	cin.get();
	return 0;
}
