//
// Created by jds on 3/3/26.
//
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <array>

#include "constants.h"
#include <random>
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
        cerr << "error: could not open file" << endl;
        throw invalid_argument("could not open file");
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
                cerr << "error: mode not recognized" << endl;
                throw invalid_argument("mode not recognized");
                break;
        }
#ifdef TIME_MODE
        out << x0 << csv_separator << wynik << csv_separator << step << endl;
#endif
    }
    return sum;
}

double trapezeIntegral(double (*fun)(double), double a, double b, int n, string filename) {
#ifdef TIME_MODE
    std::ofstream out(filename);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    cout << fixed << setprecision(6);
    out << "x0" << csv_separator << "x1" <<  csv_separator << "y0" << csv_separator << "y1" <<  csv_separator << "dx" <<  endl;
#endif
    double sum = 0;
    double step = (b - a) / n;
    double x0 = 0;
    double wynik = 0;
    double y0, y1;
    y0 = fun(a);
    for (int i = 0; i < n; i++) {
        x0 = a + i * step;
        y1 = fun(x0+step);
        sum += (step/2)*(y0+y1);
        y0 = y1;

#ifdef TIME_MODE
        out << x0 << csv_separator << x0+step <<  csv_separator << fun(x0) << csv_separator << y0 <<  csv_separator << step <<  endl;
#endif
    }

    return sum;
}


array<double, 2> funMaxMin(double (*fun)(double), double a, double b) {
    double step = (b-a)/3000, max = fun(a), min = max, wynik;
    while (a<=b) {
        wynik = fun(a);
        if (wynik > max) max = wynik;
        if (wynik < min) min = wynik;
        a += step;
    }
    array<double, 2> result;
    result[0] = min;
    result[1] = max;
    return result;
}

double montecarloIntegral(double (*fun)(double), double a, double b, int n, string filename) {
    random_device rd;
    std::uniform_real_distribution<double>  randomX(a,b);
    array<double, 2> maxmin;
    maxmin = funMaxMin(fun,a,b);
    double min = maxmin[0];
    min *= 1.05;
    double max = maxmin[1];
    max *= 1.05;
    std::uniform_real_distribution<double>  randomY(min,max);


#ifdef TIME_MODE
    std::ofstream out(filename);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    cout << fixed << setprecision(6);
    out << "x" << csv_separator << "y" << endl;
    cout << min << csv_separator << max << endl;
#endif

    double sum = 0;
    double x, y, fx;
    for (int i = 0; i < n; i++) {
        x = randomX(rd);
        y = randomY(rd);
        fx = fun(x);
        if (y > 0) {
            if ( y < fx) {
                sum += 1;
            }
        }else {
            if (y > fx) {
                sum -= 1;
            }
        }
#ifdef TIME_MODE
        out << x << csv_separator << y << endl;
#endif


    }





}