#include <iostream>
#include <vector>
#define Nt 10000

void SimpleIteration(double E, double h, int Nx, double** U) {
	FILE* cfout;
	cfout = fopen("simpsolve.xls", "w");
	fprintf(cfout, "\n\nПростая итерация\n\n");
	fprintf(cfout, "	x1	x2	x3	x4	x5	x6	x7	x8	x9	x10	x11\n");
	for (int j = 1; j < Nx; j++) {
		U[j][0] = 4 * (j - 1) * h - 1;
		std::cout << j << " " << U[j][0] << std::endl;
	}
	int n = 0;
	for (int j = 2; j < Nx; j++)
	{
		U[j][n + 1] = (U[j + 1][n] + (1 + h) * U[j - 1][n] + pow(h, 2) * (4 * (j - 1) * h - 1)) / (h + 2);
		U[1][n + 1] = 0;
		U[Nx][n + 1] = 5;
		std::cout << j << " " << U[j][n] << std::endl;
		if (abs(U[j][n + 1] - U[j][n]) <= E && n > (1 / pow(h, 2))) {
			break;
		}
		else {
			n++;
		}
	}

	for (int i = 0; i < Nt; i++)
	{
		fprintf(cfout, "t%d	", i + 1);
		for (int j = 0; j < Nx; j++)
		{
			fprintf(cfout, "%.6lf	", U[i][j]);
		}
		fprintf(cfout, "\n");
	}
	fclose(cfout);
	std::cout << "\n\n" << n << std::endl;
}

int main()
{
	double E = 0.1;
	const double h = 0.1;
	const int Nx = 1 / h;

	double** U = new double* [Nt]; // Array
	for (int i = 0; i < Nt; i++) {
		U[i] = new double[Nx];
	}
	for (int n = 0; n < Nt; n++) {
		for (int j = 0; j < Nx; j++) {
			U[n][j] = 0;
		}
	}

	SimpleIteration(E, h, Nx, U);
}