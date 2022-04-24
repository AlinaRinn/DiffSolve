#include <iostream>
#include <fstream>
#include <iomanip>

void ExplicitScheme(double deltaT, double deltaX, int Nx, int Nt, double **U)
{
	//std::ofstream out("solve.xls");
	FILE* cfout;
	cfout = fopen("solve.xls", "w");
	//std::cout << "\n\n\n\n\nЯвная схема\n\n";
	fprintf(cfout, "Явная схема\n\n");
	//out << "Явная схема\n\n";
	if ((deltaT / deltaX) <= 0.5) 
	{
		//std::cout << "Условная устойчивость\n\n";
		//out << "Условная устойчивость\n\n";
		fprintf(cfout, "Условная устойчивость\n\n");
	}
	else 
	{
		//std::cout << "Условие устойчивости не выполнено\n\n";
		//out << "Условие устойчивости не выполнено\n\n";
		fprintf(cfout, "Условие устойчивости не выполнено\n\n");
	}

	for (int i = 0; i <= Nx; i++)
	{
		for (int k = 0; k <= Nt; k++) // p. s. u(t=1,x)=0, then i just do this
		{
			U[i][k] = 0;
		}
	}

	//int n = 1;

	//while (n <= Nx)
	//{
	//	U[n][1] = pow(n * deltaT, 2);
	//	U[n][Nt] = n * deltaT + pow(n * deltaT, 2);
	//	for (int j = 2; j < Nt; j++)
	//	{
	//		U[n][j] = U[n-1][j] + (deltaT / pow(deltaX, 2)) * (U[n][j] - 2 * U[n][j-1] + U[n][j-2]) + pow(deltaT * ((j - 1) * deltaX), 2);
	//	}
	//	n++;
	//}

	int n = 0;

	while (n < Nt)
	{
		for (int j = 2; j < Nx; j++)
		{
			U[j][n+1] = U[j][n] + (deltaT / pow(deltaX, 2)) * (U[j+1][n] - 2 * U[j][n] + U[j-1][n]) + pow(deltaT * ((j - 1) * deltaX), 2);
		}
		U[1][n+1] = pow(n * deltaT, 2);
		U[Nx][n+1] = n * deltaT + pow(n * deltaT, 2);
		n++;
	}

	for (int i = 0; i <= Nx; i++)
	{
		for (int k = 0; k <= Nt; k++)
		{
			//printf("%6.4lf ", U[i][k]);
			fprintf(cfout, "%.6lf	", U[i][k]);
			//out << sprintf("%6.4lf	", U[i][k]);
			//out << U[i][k] << "	";
			//std::cout.precision(5);
			//std::cout << std::left << std::setw(10) << U[i][k] << " ";
		}
		fprintf(cfout, "\n");
		//std::cout << "\n----------------------------------------------------------------------------------------------\n";
		//out << "\n---------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
	fclose(cfout);
	//out.close();
}

void ImplicitScheme(double deltaT, double deltaX, int Nx, int Nt, double **U) {
	for (int n = 0; n < Nx; n++)
	{
		for (int j = 0; j < Nt; j++)
		{
			U[n][j] = 0;
		}
	}

	int n = 0;
	double *alfa = new double[Nx],
		   *beta = new double[Nx], //pow(n, 2) * pow(deltaT, 2),
		   *a = new double[Nx],
		   *b = new double[Nx],
		   *c = new double[Nx],
		   **e = new double*[Nx];
	for (int i = 0; i < Nx; i++) {
			e[i] = new double[Nt];
	}

	alfa[1] = 0; 
	beta[1] = pow(n, 2) * pow(deltaT, 2);

	while (n <= Nt)
	{
		for (int j = 2; j < Nx; j++)
		{
			a[j] = -1*deltaT / pow(deltaX, 2);
			b[j] = 1 + 2 * (deltaT / pow(deltaX, 2));
			c[j] = -1*deltaT / pow(deltaX, 2);
			e[j][n] = U[j][n] + (deltaT * pow((j - 1) * deltaX, 2));

			alfa[j] = (- 1 * a[j]) / (b[j] + c[j] * alfa[j - 1]);
			beta[j] = (e[j][n] - c[j] * beta[j - 1]) / (b[j] + c[j] * alfa[j - 1]);
		}
		U[Nx][n + 1] = n * deltaT + pow(n, 2) * pow(deltaT, 2);

		for (int j = Nx-1; j > 1; j--)
		{
			U[j][n + 1] = alfa[j] * U[j + 1][n + 1] + beta[j];
		}
		n++;
	}

	//std::ofstream out("solve.xls", std::ios::app);
	FILE *cfout;
	cfout = fopen("solve.xls", "a");
	//std::cout << "\n\n\n\n\n\n\nНеявная схема\n\n\n";
	fprintf(cfout, "\n\nНеявная схема\n\n");
	for (int i = 0; i <= Nx; i++)
	{
		for (int k = 0; k <= Nt; k++)
		{
			//printf("%6.4lf ", U[i][k]);
			fprintf(cfout, "%.6lf	", U[i][k]);
			//out << U[i][k] << "	";
			//out << printf("%6.4lf	", U[i][k]);
			//std::cout.precision(5);
			//std::cout << std::left << std::setw(10) << U[i][k] << " ";
		}
		fprintf(cfout, "\n");
		//std::cout << "\n----------------------------------------------------------------------------------------------\n";
		//out << "\n---------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
	fclose(cfout);
}

int main()
{
	setlocale(LC_ALL, "russian");
	//setlocale(LC_NUMERIC, "ru_RU.UTF8");
	double deltaT = 0.001, // t-step
		   deltaX = 0.1; // x-step (h)
	int Nx = 1 / deltaX, // j - x
		Nt = 1 / deltaT; // n - t

    double **U = new double* [Nx+1]; // Array
	for (int i = 0; i < Nx + 1; i++) {
		U[i] = new double[Nt + 1];
	}

	ExplicitScheme(deltaT, deltaX, Nx, Nt, U);
	ImplicitScheme(deltaT, deltaX, Nx, Nt, U);
	delete[] U;
}
