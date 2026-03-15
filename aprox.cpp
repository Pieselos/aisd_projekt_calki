//
// Created by jds on 3/3/26.
//
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <array>
#include <stdexcept>
#include "constants.h"
#include <random>
using namespace std;
#define epsilon 1e-6
double funSin(double x){ return sin(50*x);};
double funExp(double x){ return exp(x);};
double funLog(double x){ return log(x);};
double funSqr(double x){ return pow(5*x, 2)+3;};

 //#define TIME_MODE

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
    double step = (b-a)/200, max = fun(a), min = max, wynik;
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
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double>  randomX(a,b);
    array<double, 2> maxmin;
    maxmin = funMaxMin(fun,a,b);
    double min = maxmin[0];
    min *= 1.03;
    if (min>0) {
        min = 0;
    }
    double max = maxmin[1];
    max *= 1.03;
    if (max < 0) {
        max = 0;
    }
    std::uniform_real_distribution<double>  randomY(min,max);


#ifdef TIME_MODE
    std::ofstream out(filename);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    out << fixed << setprecision(6);
    out << "x" << csv_separator << "y" << endl;
    out << min << csv_separator << max << endl;
#endif

    long long sum = 0;
    double x, y, fx;
    for (int i = 0; i < n; i++) {
        x = randomX(gen);
        y = randomY(gen);
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
    return ((double)sum/n)*(b-a)*(max-min);

}


static inline pair<double,double> sobol2_32(uint32_t i) {
    // Gray code
    uint32_t g = i ^ (i >> 1);

    // Składniki bitowe
    uint32_t x_bits = 0u;
    uint32_t y_bits = 0u;

    // Kierunki (direction numbers)
    // Dla 1. wymiaru można je generować on-the-fly jako bity 1<<(31-b)
    // Dla 2. wymiaru używamy klasycznego zestawu (wielomian x^3 + x + 1)
    static const uint32_t V2[32] = {
        0x80000000u, 0x40000000u, 0xC0000000u, 0x20000000u,
        0xA0000000u, 0x60000000u, 0xE0000000u, 0x10000000u,
        0x90000000u, 0x50000000u, 0xD0000000u, 0x30000000u,
        0xB0000000u, 0x70000000u, 0xF0000000u, 0x08000000u,
        0x88000000u, 0x48000000u, 0xC8000000u, 0x28000000u,
        0xA8000000u, 0x68000000u, 0xE8000000u, 0x18000000u,
        0x98000000u, 0x58000000u, 0xD8000000u, 0x38000000u,
        0xB8000000u, 0x78000000u, 0xF8000000u, 0x04000000u
    };

    for (int b = 0; b < 32; ++b) {
        if (g & (1u << b)) {
            // Wymiar 1: bity 1<<(31-b)
            x_bits ^= (1u << (31 - b));
            // Wymiar 2: z tablicy
            y_bits ^= V2[b];
        }
    }

    // Skala do [0,1)
    const double inv2_32 = 1.0 / 4294967296.0; // 2^32
    return { x_bits * inv2_32, y_bits * inv2_32 };
}

// --- NOWA FUNKCJA: Monte Carlo (hit-or-miss) na sekwencji Sobola ---
double montecarloSobolIntegral(double (*fun)(double), double a, double b, int n, string filename)
{
    // Wyznaczenie zakresu w osi Y jak w Twojej wersji
    array<double, 2> maxmin = funMaxMin(fun, a, b);
    double min = maxmin[0] * 1.03;
    if (min > 0.0) min = 0.0;
    double max = maxmin[1] * 1.03;
    if (max < 0.0) max = 0.0;

#ifdef TIME_MODE
    std::ofstream out(filename);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    out << fixed << setprecision(6);
    out << "x" << csv_separator << "y" << endl;
    out << min << csv_separator << max << endl;
#endif

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        // i+1 żeby pominąć punkt (0,0)
        auto uv = sobol2_32(static_cast<uint32_t>(i + 1));
        double x = a   + uv.first  * (b - a);
        double y = min + uv.second * (max - min);

        double fx = fun(x);

        if (y > 0.0) {
            if (y < fx) ++sum;
        } else {
            if (y > fx) --sum;
        }

#ifdef TIME_MODE
        out << x << csv_separator << y << endl;
#endif
    }

    return (static_cast<double>(sum) / n) * (b - a) * (max - min);
}
