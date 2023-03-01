#include <iostream>

using namespace std;

double lagrange(double* x, double* y, int n, double _x)
{
	double result = 0.0;

	for (int i = 0; i < n; i++)
	{
		double P = 1.0;

		for (int j = 0; j < n; j++)
			if (j != i)
				P *= (_x - x[j]) / (x[i] - x[j]);

		result += P * y[i];
	}	
	return result;
}

int main()
{
	int n = 4;
	double _x =3.15;
	double *X = new double[n];
	double *Y = new double[n];
	X[0] = 1; Y[0] = 1;
	X[1] = 2; Y[1] = 4; 
    X[2] = 3; Y[2] = 9;
	X[3] = 4; Y[3] = 16;




	//X[0] = 1.0; Y[0] = exp(-X[0]);
	//for (int i = 1; i < n; ++i)
	//{
	//	X[i] = X[i - 1] + 0.01; 
	//	Y[i] = exp(-X[i]);
	//}
	////X[0] = 1.0; Y[0] = 0;
	////X[1] = 1.01; Y[1] = 0.5;
	//cout << "X = " << _x << " - Y = " << exp(-_x) << endl;

	cout << "X = " << _x << " - Y = " << lagrange(X, Y, n, _x) << endl;
	cin.get();
	return 0;
}