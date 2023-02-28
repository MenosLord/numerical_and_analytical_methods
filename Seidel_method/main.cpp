#include <iostream>
#include <cmath>

using namespace std;

void freeM(double **M, int n);
double normX(double *newX, double *oldX, int n);
void DiagonalM(double **M, double **D, int n);
void LowM(double **M, double **L, int n);
void UpM(double **M, double **U, int n);
void MxV(double **M, double *V, int n);
void AxB(double **A, double **B, int n);
void CopyAtoB(double **A, double **B, int n);
int Zeidel(double **L, double **D, double **U, double *B, double *X, int n, double e);

int main()
{
	double eps = 0.0000001;

	int n = 3;
	double **A = new double *[n];
	double **L = new double *[n];
	double **U = new double *[n];
	double **D = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
		L[i] = new double[n];
		U[i] = new double[n];
		D[i] = new double[n];
	}
	double *b = new double[n];
	double *x = new double[n];

		A[0][0] = 5.0;   A[0][1] = -1.0;	    A[0][2] = 1.0;	    	b[0] = -6.0;	// x[0] = 1;
		A[1][0] = -2.0;	 A[1][1] = 5.0;		    A[1][2] = 1.0;			b[1] = 13.0;	// x[1] = 1;
		A[2][0] = 3.0;	 A[2][1] = -1.0;		A[2][2] = 5.0;          b[2] = 0.0;	    // x[2] = 1;
		
    

	DiagonalM(A, D, n);
	LowM(A, L, n);
	UpM(A, U, n);
	for (int i = 0; i < n; ++i)
		x[i] = b[i];

	cout << "Iterations k = " << Zeidel(L, D, U, b, x, n, eps) << endl;
	
	for(int i = 0; i < n; ++i)
		cout << "X[" << i << "] =\t" << x[i] << endl;

	delete[] b;
	delete[] x;
	freeM(A, n);
	freeM(L, n);
	freeM(D, n);
	freeM(U, n);
	cin.get();
	return 0;
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

void DiagonalM(double **M, double **D, int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if (i == j)
				D[i][j] = 1.0 / M[i][j];
			else
				D[i][j] = 0.0;
}

void LowM(double **M, double **L, int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if (i > j)
				L[i][j] = M[i][j];
			else
				L[i][j] = 0.0;
}

void UpM(double **M, double **U, int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if (i < j)
				U[i][j] = M[i][j];
			else
				U[i][j] = 0.0;
}

void MxV(double **M, double *V, int n)
{
	double *R = new double[n];
	for (int i = 0; i < n; ++i)
	{
		R[i] = 0.0;
		for (int j = 0; j < n; ++j)
			R[i] += M[i][j] * V[j];
	}
	for (int i = 0; i < n; ++i)
		V[i] = R[i];

	delete [] R;
}

void AxB(double **A, double **B, int n)
{
	double **R = new double *[n];
	for (int i = 0; i < n; i++)
		R[i] = new double[n];

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			R[i][j] = 0.0;
			for(int k = 0; k < n; ++k)
				R[i][j] += A[i][k] * B[k][j];
		}

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			A[i][j] = R[i][j];

	freeM(R, n);
}

void CopyAtoB(double **A, double **B, int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			B[i][j] = A[i][j];
}

int Zeidel(double **L, double **D, double **U, double *B, double *X, int n, double e)
{
	int k = 0;
	double err = 0.0;
	double *XL = new double[n];
	double *XU = new double[n];
	double *Xn = new double[n];

	double **RL = new double *[n];
	double **RU = new double *[n];
	for (int i = 0; i < n; i++)
	{
		RL[i] = new double[n];
		RU[i] = new double[n];
	}
	CopyAtoB(D, RL, n);
	CopyAtoB(D, RU, n);

	AxB(RL, L, n);
	AxB(RU, U, n);
	MxV(D, B, n);

	for (int i = 0; i < n; ++i)
		Xn[i] = 0.0;

	do
	{
		k++;
		for (int i = 0; i < n; ++i)
		{
			XL[i] = Xn[i];
			XU[i] = X[i];
		}
		MxV(RL, XL, n);
		MxV(RU, XU, n);

		for (int i = 0; i < n; ++i)
			Xn[i] = B[i] - XL[i] - XU[i];
		err = normX(X, Xn, n);
		
		for (int i = 0; i < n; ++i)
			X[i] = Xn[i];
	} while (err > e);
	
	freeM(RL, n);
	freeM(RU, n);
	delete [] XL;
	delete [] XU;
	delete [] Xn;
	return k;
}
