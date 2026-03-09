#include <iostream>
#include "aprox.h"
#include "constants.h"
#include <cmath>
#include <fstream>
#include <chrono>
using namespace std;

int main() {
    ofstream out("times.csv",ios::app);
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    out << fixed << setprecision(6);
    double integral = 0;
    auto t0 = chrono::high_resolution_clock::now();
    // integral = classicIntegral(&funSin, 0, 5, 15, 1, "sin.csv");
    integral = trapezeIntegral(funSin,1,6,15,"trapezy.csv");
    cout << integral << endl;
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> dt = t1 - t0;
    // out << "classicIntegralLeft" << csv_separator << 100 << csv_separator << dt.count() << endl;



}
