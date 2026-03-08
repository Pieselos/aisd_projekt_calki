//
// Created by jds on 3/3/26.
//
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>

#include "constants.h"
#define epsilon = 0.0000001
using namespace std;
double funSin(double x){ return sin(50*x);};
double funExp(double x){ return exp(x);};
double funLog(double x){ return log(x);};
double funSqr(double x){ return pow(5*x, 2)+3;};

#define TIME_MODE

double classicIntegral(double (*fun)(double), double a, double b, int n, int mode, string filename) {
#ifdef TIME_MODE
    std::ofstream out(filename);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    cout << fixed << setprecision(6);
    out << "x0" << csv_separator << "y" << csv_separator << "dx" <<  endl;
#endif
    double sum = 0;
    double step = (b - a) / n;
    double x0 = 0;
    double wynik = 0;
    for (int i = 0; i < n; i++) {
        x0 = a + i * step;

        switch (mode) {
            case 0:
                //left
                wynik = fun(x0);
                sum +=  wynik * step;
                break;
            case 1:
                //center
                wynik = fun(x0 + step/2);
                sum += wynik * step;
                break;
            case 2:
                //right
                wynik = fun(x0 + step);
                sum += wynik * step;
                break;
            default:
                cerr << "Error: Mode not recognized" << endl;
                throw invalid_argument("Mode not recognized");
                break;
        }
#ifdef TIME_MODE
        out << x0 << csv_separator << wynik << csv_separator << step << endl;
#endif
    }
    return sum;
}