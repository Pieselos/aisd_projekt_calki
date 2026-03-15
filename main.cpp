#include <iostream>
#include "aprox.h"
#include "constants.h"
#include <cmath>
#include <fstream>
#include <chrono>
using namespace std;

int main() {
    ofstream out("precision.csv");
    if (!out) {
        cerr << "Error: Could not open file" << endl;
        throw invalid_argument("Could not open file");
    }
    out << fixed << setprecision(10);
    // out << "n" << csv_separator << "t[us]" << endl;
    double integral = 0;
    // integral = classicIntegral(&funSin, 0, 5, 15, 1, "sin.csv");
    // integral = trapezeIntegral(funSin,1,6,15,"trapezy.csv");
    for (int i=3; i<1000; i+=2) {
       out << i << csv_separator <<  montecarloSobolIntegral(*funSin,1,5,i,"montecarlo.svd") << endl;
        //     auto t0 = chrono::high_resolution_clock::now();
        //         for (int j=0; j<100; j++) {
        //             montecarloSobolIntegral(*funsin,1,5,i,"jajo.svd");
        //         }
        // // out << i << csv_separator << montecarloIntegral(*funLog,1,5,i,"precision.csv") << endl;
        //     auto t1 = chrono::high_resolution_clock::now();
        //     chrono::duration<double, micro> dt = t1 - t0;
        //     out << i << csv_separator << dt.count()/100 << endl;
    }

    //}
    // for (int i=3; i<250; i++) {
    //     out << i << csv_separator << trapezeIntegral(*funSin,1,5,i,"precision.cvs") << endl;
    // }


    // integral = montecarloIntegral(funSin,1,5,150,"montecarlo.csv");
    // cout << integral << endl;
    // ;
    // out << "classicIntegralLeft" << csv_separator << 100 << csv_separator << dt.count() << endl;



}
