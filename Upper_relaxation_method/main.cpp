#include <iostream>
#include <cmath>

using namespace std;

void printM(double **M, int n);
void printV(double *V, int n);
void printX(double *V, int n);
void freeM(double **M, int n);
double normX(double *newX, double *oldX, int n);
double normM(double **M, int n);
int Relax(double **M, double *d, double *X, int n, double w, double e);

int main()
{
	double w = 0.5;
	double eps = 0.0000001;
	
	int n = 3;
	double **A = new double *[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[n];
	double *b = new double[n];
	double *x = new double[n];
	double **C = new double *[n];
	for (int i = 0; i < n; i++)
		C[i] = new double[n];
	   
	    A[0][0] = 5.0;   A[0][1] = -1.0;	    A[0][2] = 1.0;	    	b[0] = -6.0;	
		A[1][0] = -2.0;  A[1][1] = 5.0;         A[1][2] = 1.0;         b[1] = 13.0;	
		A[2][0] = 3.0;   A[2][1] = -1.0;	    A[2][2] = 5.0;         b[2] = 0.0;	

	
	//A[0][0] = 5.0;  A[0][1] = -1.0;	    A[0][2] = 2.0;     b[0] = 8.0;
	//A[1][0] = 1.0;	 A[1][1] = 4.0;	    A[1][2] = -1.0;    b[1] =-4.0;
	//A[2][0] = 1.0;	 A[2][1] = 1.0;		A[2][2] = 4.0;     b[2] = 4.0;
	////==================================================================================================================
		//A[0][0] = 100.0; A[0][1] = -80.0;	A[0][2] = 5.0;	    A[0][3] = -24.0;	b[0] = 1.0;	// x[0] = -1;
		//A[1][0] = 1.0;	 A[1][1] = 2.0;		A[1][2] = -1.0;		A[1][3] = 1.0;		b[1] = 3.0;	// x[1] = 1;
		//A[2][0] = 7.0;	 A[2][1] = 8.0;		A[2][2] = -14.0;    A[2][3] = 1.0;	    b[2] = 2.0;	// x[2] = 1;
		//A[3][0] = 1.0;	 A[3][1] = -7.0;	A[3][2] = -4.0;		A[3][3] = 8.0;		b[3] = -2.0;	// x[2] = 1;
	////==================================================================================================================
	//A[0][0] = 8;	A[0][1] = 1;		A[0][2] = -4; b[0] = 6 ;
	//A[1][0] = 2;	A[1][1] = -6;		A[1][2] = 1;  b[1]= -9;
	//A[2][0] = -1;	A[2][1] = 1;		A[2][2] = 4;  b[2] = 5;
	//==================================================================================================================
	//A[0][0] = 20.9;	A[0][1] = 1.2;		A[0][2] = 2.1;	A[0][3] = 0.9;		b[0] = 21.7;	// x[0] = 0.7999;
	//A[1][0] = 1.2;	A[1][1] = 21.2;		A[1][2] = 1.5;		A[1][3] = 2.5;		b[1] = 27.46;	// x[1] = 0.9999;
	//A[2][0] = 2.1;	A[2][1] = 1.5;		A[2][2] = 19.8;		A[2][3] = 1.3;	b[2] = 28.76;	// x[2] = 1.1999;
	//A[3][0] = 0.9;	A[3][1] = 2.5;	A[3][2] = 1.3;		A[3][3] = 32.1;		b[0] = 4.0;b[3] = 49.72;	// x[2] = 1.3999;
//==================================================================================================================

	cout << "A =" << endl;
	printM(A, n);
	printV(b, n);

	for (int i = 0; i < n; ++i) //создаем — матрицу
	{
		for (int j = 0; j < n; ++j)
		{
			C[i][j] = -A[i][j] / A[i][i];
		}
		b[i] /= A[i][i];
		x[i] = b[i];
		C[i][i] = 0.0;
	}
	//double q = normM(C, n); 

	cout << "w = " << w << endl;
	cout << "eps = " << eps << endl;
	cout << "Iterations k = " << Relax(C, b, x, n, w, eps) << endl << endl;
	printX(x, n);

	delete[] b;
	delete[] x;
	freeM(A, n);
	freeM(C, n);
	cin.get();
	return 0;
}

void printM(double **M, int n) //выводит матрицу
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout.width(8);
			cout << M[i][j] << "\t";
		}
		cout << endl;
	}
}

void printV(double *V, int n) // выводим вектор
{
	for (int i = 0; i < n; ++i)
	{
		cout << "b["<< (i + 1) <<"] = "; 
		cout.width(8);
		cout << V[i] << endl;
	}
	cout << endl;
}

void printX(double *V, int n) // выводим ’
{
	for (int i = 0; i < n; ++i)
	{
		cout << "x["<< (i + 1) <<"] = "; 
		cout.width(8);
		cout << V[i] << endl;
	}
	cout << endl;
}

void freeM(double **M, int n)
{
	for (int i = 0; i < n; ++i)
		delete[] M[i];
	delete[] M;
}

double normX(double *newX, double *oldX, int n) //норма вектора
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

double normM(double **M, int n) //норма матрицы
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

int Relax(double **M, double *d, double *X, int n, double w, double e)
{
	int k = 0;
	double tmp = 0.0;
	double *P = new double[n];
	do
	{
		k++;
		for (int i = 0; i < n; ++i)
		{
			tmp = 0.0;
			P[i] = X[i];
			for (int j = 0; j < n; ++j)
			{
				tmp += M[i][j] * X[j];
			}
			X[i] = (1 - w) * X[i] + w * (tmp + d[i]);
		}
	} while (normX(X, P, n) > e);
	delete[] P;
	return k;
}