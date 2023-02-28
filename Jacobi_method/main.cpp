#include <iostream>
#include <cmath>

using namespace std;

void printM(double **M, int n);
void printV(double *V, int n);
void freeM(double **M, int n);
double normX(double *newX, double *oldX, int n);
double normM(double **M, int n);
bool isUsed(double **M, int n);
int Jakoby(double **M, double *d, double *X, int n, double e);

int main()
{
	double eps = 0.001;

	int n = 4;
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[n];
	double *b = new double[n];
	double *x = new double[n];
	double **C = new double *[n];
	for (int i = 0; i < n; i++)
		C[i] = new double[n];

		//A[0][0] = 100.0; A[0][1] = -80.0;	A[0][2] = 5.0;	    A[0][3] = -24.0;	b[0] = 1.0;	// x[0] = -1;
		//A[1][0] = 1.0;	 A[1][1] = 2.0;		A[1][2] = -1.0;		A[1][3] = 1.0;		b[1] = 3.0;	// x[1] = 1;
		//A[2][0] = 7.0;	 A[2][1] = 8.0;		A[2][2] = -14.0;    A[2][3] = 1.0;	    b[2] = 2.0;	// x[2] = 1;
		//A[3][0] = 1.0;	 A[3][1] = -7.0;	A[3][2] = -4.0;		A[3][3] = 8.0;		b[3] = -2.0;	// x[2] = 1;
	A[0][0] = 20.9;	A[0][1] = 1.2;		A[0][2] = 2.1;	    A[0][3] = 0.9;		b[0] = 21.7;	// x[0] = 0.7999;
	A[1][0] = 1.2;	A[1][1] = 21.2;		A[1][2] = 1.5;		A[1][3] = 2.5;		b[1] = 27.46;	// x[1] = 0.9999;
	A[2][0] = 2.1;	A[2][1] = 1.5;		A[2][2] = 19.8;		A[2][3] = 1.3;	    b[2] = 28.76;	// x[2] = 1.1999;
	A[3][0] = 0.9;	A[3][1] = 2.5;	    A[3][2] = 1.3;		A[3][3] = 32.1;		b[3] = 49.72;	// x[2] = 1.3999;
//==================================================================================================================
//	A[0][0] = 0.98;	A[0][1] = 0.64;		A[0][2] = -0.35;	A[0][3] = 0.65;		b[0] = -0.04;	// x[0] = -1;
//	A[1][0] = 0.42;	A[1][1] = 0.89;		A[1][2] = 0.24;		A[1][3] = 0.48;		b[1] = 1.19;	// x[1] = 1;
//	A[2][0] = 0.37;	A[2][1] = 0.72;		A[2][2] = 0.79;		A[2][3] = -0.25;	b[2] = 0.89;	// x[2] = 1;
//	A[3][0] = 0.63;	A[3][1] = -0.57;	A[3][2] = 0.41;		A[3][3] = 0.91;		b[3] = 0.12;	// x[2] = 1;
//==================================================================================================================
//==================================================================================================================
	//A[0][0] =0.11;	A[0][1] = 0.88;		A[0][2] = 0.12;	    A[0][3] = 0.15;		b[0] = 0.15;	// x[0] = 0.7999;
	//A[1][0] = 1.23;	A[1][1] = -0.75;	A[1][2] = -0.75;	A[1][3] = -0.24;	b[1] = 0.24;	// x[1] = 0.9999;
	//A[2][0] = 5.6;	A[2][1] = 10;		A[2][2] = 0.17;		A[2][3] = -0.18;	b[2] = 1.17;	// x[2] = 1.1999;
	//A[3][0] = 1.73;	A[3][1] = 2.11;	    A[3][2] = 0.35;		A[3][3] = -0.8;		b[3] = 0;	// x[2] = 1.3999;
//==================================================================================================================

	if (!isUsed(A, n))
	{
		cout << "Wrong conditions!!!\nEnd program...\nPress Enter to exit..." << endl; //сделать диагональное преобладание в Зейделе, Якоби, Релаксации 
		cin.get();
		return 0;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			C[i][j] = -A[i][j] / A[i][i];
		}
		b[i] /= A[i][i];
		x[i] = b[i];
		C[i][i] = 0.0;
	}
	double q = normM(C, n);

	printM(C, n);
	if (q < 0.5)
		cout << "Iterations k = " << Jakoby(C, b, x, n, eps) << endl;
	else
		cout << "Iterations k = " << Jakoby(C, b, x, n, ((1 - q) * eps / q)) << endl;
	cout << endl;
	printV(x, n);

	delete[] b;
	delete[] x;
	freeM(A, n);
	freeM(C, n);
	cin.get();
	return 0;
}

void printM(double **M, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << M[i][j] << "\t";
		cout << endl;
	}
}

void printV(double *V, int n)
{
	for (int i = 0; i < n; ++i)
		cout << V[i] << "\t";
	cout << endl;
}

void freeM(double **M, int n)
{
	for (int i = 0; i < n; ++i)
		delete[] M[i];
	delete[] M;
}
//Находит покомпонентную разность и выбираемм макс
double normX(double *newX, double *oldX, int n)
{
	double T;
	double mx = fabs(newX[0] - oldX[0]);
	for (int i = 1; i < n; ++i)
	{
		T = fabs(newX[i] - oldX[i]);
		if (T > mx)
			mx = T;
	}
	return mx;
}
//Находим строку с максимальной суммой элементов в строке, возвращет максимальную сумму этой строки среди всех строк
double normM(double **M, int n)
{
	double *T = new double[n];
	for (int i = 0; i < n; ++i)
	{
		T[i] = 0.0;
		for (int j = 0; j < n; ++j)
			T[i] += fabs(M[i][j]);
	}
	double mx = T[0];
	for (int i = 1; i < n; ++i)
		if (mx < T[i])
			mx = T[i];
	delete[] T;
	return mx;
}

bool isUsed(double **M, int n)
{
	double *T = new double[n];
	for (int i = 0; i < n; ++i)
	{
		T[i] = 0.0;
		for (int j = 0; j < n; ++j)
			if (j != i) T[i] += fabs(M[i][j]);
	}
	bool mx = true;
	for (int i = 0; i < n; ++i)
		if (fabs(M[i][i]) < T[i])
			mx = false;
	delete[] T;
	return mx;
}

int Jakoby(double **M, double *d, double *X, int n, double e)
{
	int k = 0;
	double tmp = 0.0;
	double *P = new double[n];
	double *T = new double[n];
	do
	{
		k++;
		for (int i = 0; i < n; ++i)
		{
			T[i] = 0.0;
			P[i] = X[i];
			for (int j = 0; j < n; ++j)
			{
				T[i] += M[i][j] * X[j];
			}
			T[i] += d[i];
		}
		for (int i = 0; i < n; ++i)
			X[i] = T[i];
	} while (normX(X, P, n) > e);
	delete[] P;
	delete[] T;
	return k;
}