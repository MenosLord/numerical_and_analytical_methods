#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n = 3;
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[n];
	double *b = new double[n];
	double *x = new double[n];

	A[0][0] = 6.214;  A[0][1] =2.18;    A[0][2] = 3.184;    b[0] = 49.91;	    // x[0] = 3;
	A[1][0] = -1.351; A[1][1] =8.224;   A[1][2] = 5.224;    b[1] = 50.17;	// x[1] = 5;
	A[2][0] = 2.489;  A[2][1] = -0.459; A[2][2] = 4.299;    b[2] = 32.68;	// x[2] = 4;

/*
	A[0][0] = 2;	A[0][1] = 1;	A[0][2] = -1;	b[0] = 8;	// x[0] = 2;
	A[1][0] = -3;	A[1][1] = -1;	A[1][2] = 2;	b[1] = -11;	// x[1] = 3;
	A[2][0] = -2;	A[2][1] = 1;	A[2][2] = 2;	b[2] = -3;	// x[2] = -1;

	A[1][1] = 6.214;	A[1][2] = 2.18;		A[1][3] = 3.184;	b[1] = 49.91;	
	A[2][1] = -1.351;	A[2][2] = 8.224;	A[2][3] = 5.224;	b[2] = 50.17;	
	A[3][1] = 2.489;	A[3][2] = -0.459;	A[3][3] =4.299;		b[3] = 32.68;	
*/

	int i, j, k;
	double d, s;

	for (k = 0; k < n; k++) // прямой ход
	{
		for (j = k + 1; j < n; j++)
		{
			d = A[j][k] / A[k][k]; 
			for (i = k; i < n; i++)
			{
				A[j][i] = A[j][i] - d * A[k][i]; 
			}
			b[j] = b[j] - d * b[k]; 
		}
	}
	for (k = n-1; k >= 0; k--) // обратный ход
	{
		d = 0;
		for (j = k + 1; j < n; j++)
		{
			s = A[k][j] * x[j]; 
			d = d + s; 
		}
		x[k] = (b[k] - d) / A[k][k]; 
	}
	cout << "Korni sistemy: " << endl;
	for (i = 0; i < n; i++)
		cout << "x[" << i << "]=" << x[i] << " " << endl;


	cin.get();
	cin.get();
	return 0;
}