// Найти экстремум функции F(X) одним из четырех методов (методом золотого сечения, методом ломаных, методом касательных, методом Ньютона). 
// Желательно запрограммировать на любом языке программирования или в Матлаб.
// 22 2x^2-12x min [0; 2] 0.01

#include <iostream>

const double GOLDEN_NUMBER = 1.6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374;
const double E = 0.00000000000001, // Error
             A = 0,    // Upper bound
             B = 2;    // Lower bound

double function(double x) {
    return 2 * x * x - 12 * x;
}

double search(double A, double B, double GLDN_NMBR, int &iter) {
    double x1 = 0, x2 = 0;
    double fx1 = 0, fx2 = 0;

    while (abs(B-A) > E) {
        x1 = B - ((B - A) / GLDN_NMBR);
        x2 = A + ((B - A) / GLDN_NMBR);
        fx1 = function(x1);
        fx2 = function(x2);
        if (fx1 >= fx2) {
            A = x1;
        }
        else {
            B = x2;
        }
        iter++;
    }

    return (A + B) / 2;
}

int main()
{
    int iter = 0;
    double minimum = search(A, B, GOLDEN_NUMBER, iter);

    std::cout << "Minmum of stated function is: " << minimum
              << "\nFunction value in this point is: " << function(minimum)
              << "\nIteration count: " << iter << "\n\n\n";

    system("pause");
}