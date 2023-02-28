#include <iostream>
#include <cmath>

using namespace std;

void printM(double **M, int n);
void printV(double *V, int n);
void delColRow(double **M, double **T, int n, int di, int dj); //удаляет di строку и dj столбец, выдает матрицу Т
void freeM(double **M, int n);
double det(double **M, int n);
void Transposition(double **M, int n);
void inverseMatrix(double **M, double **InvM, int n);
void MtoV(double *R, double **M, double *V, int n); // умножаем матрицу на вектор, получаем R

int main()
{
	int n = 3;
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[n];
	double *b = new double[n];
	double *x = new double[n];
	double **InvA = new double *[n];
	for (int i = 0; i < n; i++)
		InvA[i] = new double[n];


	double **Temp = new double *[n - 1];
	for (int i = 0; i < n - 1; i++)
		Temp[i] = new double[n - 1];

	
	A[0][0] =4;	A[0][1] = 1;		A[0][2] =2;    b[0] =-6;
	A[1][0] =0;	A[1][1] =3;		A[1][2] =1; 	b[1] =-1;
	A[2][0] =1;	A[2][1] =2;		A[2][2] =4;     b[2] =-5;

		//A[0][0] = 0.98;	A[0][1] = 0.64;		A[0][2] = -0.35;	A[0][3] = 0.65;		b[0] = -0.04;	// x[0] = -1;
		//A[1][0] = 0.42;	A[1][1] = 0.89;		A[1][2] = 0.24;		A[1][3] = 0.48;		b[1] = 1.19;	// x[1] = 1;
		//A[2][0] = 0.37;	A[2][1] = 0.72;		A[2][2] = 0.79;		A[2][3] = -0.25;	b[2] = 0.89;	// x[2] = 1;
		//A[3][0] = 0.63;	A[3][1] = -0.57;	A[3][2] = 0.41;		A[3][3] = 0.91;		b[3] = 0.12;	// x[2] = 1;
	//A[0][0] = 2;	A[0][1] = -4;		A[0][2] = 3;	b[0] = 1;	// x[0] = -1;
	//A[1][0] = 1;	A[1][1] = -2;		A[1][2] = 4;	b[1] = 3;	// x[1] = 0;
	//A[2][0] = 3;	A[2][1] = -1;		A[2][2] = 5;	b[2] = 2;	// x[2] = 1;
	
	printM(A, n);
	cout << endl << det(A, n) << endl;
	inverseMatrix(A, InvA, n);
	cout << endl;
	printM(InvA, n);
	MtoV(x, InvA, b, n);
	cout << endl;
	printV(x, n);

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

void delColRow(double **M, double **T, int n, int di, int dj)
{
	int ki = 0;
	int kj = 0;
	for (int i = 0; i < n; ++i)
	{
		if (i != di)
		{
			for (int j = 0, kj = 0; j < n; ++j)
			{
				if (j != dj)
				{
					T[ki][kj] = M[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
}

void freeM(double **M, int n)
{
	for (int i = 0; i < n; ++i)
		delete[] M[i];
	delete[] M;
}

double det(double **M, int n)
{
	double res = 0.0;
	int m = n - 1;
	int u = 1;

	if (n == 1)
		res = M[0][0];
	else if (n == 2)
		res = M[0][0] * M[1][1] - M[0][1] * M[1][0];
	else if (n == 3)
		res = M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[2][1] * M[1][0] - M[0][2] * M[1][1] * M[2][0] - M[0][1] * M[2][2] * M[1][0] - M[0][0] * M[1][2] * M[2][1];
	else
	{
		double **T = new double *[m];
		for (int i = 0; i < m; i++)
			T[i] = new double[m];
		for (int i = 0; i < n; ++i)
		{
			delColRow(M, T, n, 0, i);
			res += u * M[0][i] * det(T, m);
			u = -u;
		}
		freeM(T, m);
	} 

	return res;
}

void Transposition(double **M, int n)
{
	double tmp = 0.0;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			tmp = M[i][j];
			M[i][j] = M[j][i];
			M[j][i] = tmp;
		}
}

void inverseMatrix(double **M, double **InvM, int n)
{
	int m = n - 1;
	double **T = new double *[m];
	for (int i = 0; i < m; i++)
		T[i] = new double[m];

	double D = 1.0 / det(M, n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			delColRow(M, T, n, i, j);
			InvM[i][j] = pow(-1.0, (i + j)) * det(T, m) * D;
		}
	}
	freeM(T, m);
	Transposition(InvM, n);
}

void MtoV(double *R, double **M, double *V, int n)
{
	for (int i = 0; i < n; ++i)
	{
		R[i] = 0.0;
		for (int j = 0; j < n; ++j)
			R[i] += M[i][j] * V[j];
	}
}