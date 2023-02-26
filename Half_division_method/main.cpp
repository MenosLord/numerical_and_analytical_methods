#include <iostream>
#include <cmath>
using namespace std;
 
double func(double x)
{
    return x+pow(x,(1/2))+pow(x,(1/3))-2.5;
}
int main()
{
    setlocale(LC_ALL,"Russian");
	cout.precision();
    const double eps = 0.0001;
    double a, b, t, f1, f2, x, k = 0;
    cout <<"Введите отрезок где предположительно расположен корень уравнения!";
    cout << "\nВведите a= ";
	cin >> a;
    cout << "Введите b= ";
	cin >> b;

    do
    {
		k++;
		f1 = func(a);
		t = (a + b) / 2;
		f2 = func(t);
		if (f1 * f2 <= 0) 
			b = t;
		else 
			a = t;
    } while (fabs(b - a) > eps);
    x = (a + b) / 2.0;
    f1 = func(x);
    if (fabs(f1) <= 0.0001)
    {
		cout <<"\nКорень уравнения с погрешностью " << fixed << eps <<", X= "  << x << " k=" << k;
		cout <<"\nЗначение функции F(X)= "<< f1;
	   
    }
    else 
		cout <<"На данном отрезке уравнение корней не имеет!";
    cin.get();
	cin.get();
    return 0;
}