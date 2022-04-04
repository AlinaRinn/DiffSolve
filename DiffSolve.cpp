#include <iostream>
#include <vector>

int main()
{
	float deltaT = 0.1, // t-step
		  deltaX = 0.1, // x-step (h)
	   	  x = 0,        // variable 1 (temperature)
		  t = 0,        // variable 2 (time)
		  Unj = 0,      // initial condition
		  Unplus1j = 0, // function U in point with accordance t(n), x(j)
		  Ulbc = 0,     // left boundary condition
		  Urbc = 0;     // right boundary condition

	int n = 0, // point position on axis t(n)
		M = 10, // end of axis t(n)

		j = 1, // point position on axis x(j)
		N = 10; // end of axis x(j)

	std::vector<float> vect;

	while (n <= M)
	{
		for (j = 2; j < N - 1; j++)
		{
			Unplus1j = Unj + (deltaT / pow(deltaX, 2)) * (Unj + deltaX - 2 * Unj + Unj - deltaX) + pow(deltaT * ((j - 1) * deltaX), 2);
			Unj = Unplus1j;
			vect.push_back(Unj);
		}
		Ulbc = pow(n * deltaT, 2);
		Urbc = n * deltaT + 1;
		n++;
	}

	for (int i = 0; i < vect.size(); i++)
	{
		std::cout << vect[i] << " ";
	}
	

	std::cout << "\n" << Unj;
}
