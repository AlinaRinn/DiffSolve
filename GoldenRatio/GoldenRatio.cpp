// Найти экстремум функции F(X) одним из четырех методов (методом золотого сечения, методом ломаных, методом касательных, методом Ньютона). 
// Желательно запрограммировать на любом языке программирования или в Матлаб.
// Дано: 
// Вариант 22 
// Функция 2x^2-12x 
// Экстремум min 
// Интервал поиска [0; 2] 
// Точность 0.01 
// Метод золотого сечения

#include <iostream>
#include <chrono>
#include <vector>

const double GOLDEN_NUMBER = 1.6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374;
const double E = 0.01,  // Error
             A = 0,     // Upper bound
             B = 2;     // Lower bound

double function(double x) {
    return 2 * x * x - 12 * x;
    //return exp(-2*pow(x,15))+x*x/2-log(45);
}

double search(double A, double B, double GLDN_NMBR, int &iter) {
    double x1 = 0, x2 = 0;
    double fx1 = 0, fx2 = 0;

    // I dont make iteration constraint because i cant cause inf loop at any meaningful error value. Also dont want make program slower. Can add, if needed
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

void printCSV(double** graph)
{
    FILE* f = fopen("graph.csv", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "x;f(x);\n\n");
    for (int i = 0; i <= 1/E; i++)
    {
        fprintf(f, "%.5lf;%.10lf\n", graph[i][0], graph[i][1]);
    }

    fclose(f);
}

void graph_generator(double A, double B, double **graph, double increment = E){
    double step = abs(B - A) * increment;
    for (int i = 0; i <= 1/E; i++) {
        graph[i][0] = A;
        graph[i][1] = function(A);
        A += step;
    }
}

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    int iter = 0;
    double minimum = search(A, B, GOLDEN_NUMBER, iter),
           func = function(minimum);
    auto end = std::chrono::high_resolution_clock::now();

    double** graph = new double* [1/E]; 
    for (int i = 0; i <= (1/E); i++) {
        graph[i] = new double[2];
    }
    graph_generator(A, B, graph);
    printCSV(graph);

    std::cout << "Minmum of given function is:      " << minimum
              << "\nFunction value in this point is: " << func;
   
    std::chrono::duration<float> duration = end - begin;

    std::cout << "\nRuntime: " << (float)duration.count() << " sec"
              << "\nIteration count: " << iter << "\nError: " << E << "\n\n\n";


    for (int count = 0; count < 2; count++) {
        delete[] graph[count];
    }
    system("pause");
}




