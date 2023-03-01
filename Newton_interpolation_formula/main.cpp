#include <iostream>

using namespace std;

double Newton(double* x, double* y, int n, double _x)
{
	int k = n - 1;
	double result = y[0];

	double **div = new double *[n];
	for (int i = 0; i < n; i++)
		div[i] = new double[n - i];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < (n - i); j++)
			div[i][j] = 0.0;

	for (int i = 0; i < n; i++)
		div[i][0] = y[i];


	for (int j = 1; j < n; j++)
		for (int i = 0; i < k; i++)
			div[i][j] = (div[i + 1][j - 1] - div[i][j - 1]) / (x[i + j] - x[i]);
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < (n - i); j++)
		{
			cout.width(10);
			cout << div[i][j];
		}
		cout << endl;
	}
	cout << "F(x) = ";
	for(int j = k; j > 0; j--)
	{
		double r = 1.0;
		cout << " + " << div[0][j];
		for(int i = j; i > 0; i--)
		{
			r *= _x - x[i - 1];
			cout<<"*(x - "<<x[i-1]<<")";
		}
		result += (r * div[0][j]);
	}
	if (y[0] < 0.0)
		cout << " " << y[0]<< endl;
	else
		cout << " + " << y[0]<< endl;
	return result;
}

int main()
{
	int n = 4;
	double _x = 1.07;
	double *X = new double[n];
	double *Y = new double[n];
	X[0] = 1.01; Y[0] = 2.7456;
	X[1] = 1.05; Y[1] = 2.8577;
	X[2] = 1.08; Y[2] = 2.9447;
	X[3] = 1.13; Y[3] = 3.0957;

	//X[0] = 1.1; Y[0] = 1.22;
	//X[1] = 1.4; Y[1] = 1.96;
	//X[2] = 1.7; Y[2] = 2.89;
	//X[3] = 2.2; Y[3] = 4.84;
	//X[4] = 2.3; Y[4] = 5.29;
	//X[5] = 2.6; Y[5] = 6.76;
	//X[6] = 2.9; Y[6] = 8.42;
	cout << "x = " << _x << endl << "Y = " << Newton(X, Y, n, _x) << endl;

	cin.get();
	delete[] X;
	delete[] Y;
	return 0;
}//Нужно чтобы выдавал еще и функцию.