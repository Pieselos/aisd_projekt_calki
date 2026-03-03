//
// Created by jds on 3/3/26.
//
#include <cmath>
#include <iostream>
#include <ostream>
using namespace std;
double funSin(double x){ return sin(5*x);};
double funExp(double x){ return exp(x);};
double funLog(double x){ return log(x);};
double funSqr(double x){ return pow(5*x, 2)+3;};


void classicIntegral(double (*fun)(double), double a, double b, int mode) {
    cout << fun(1.5) << endl;


}