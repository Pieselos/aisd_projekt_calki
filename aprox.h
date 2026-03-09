//
// Created by jds on 3/4/26.
//
#pragma once

double funSin(double x);
double funExp(double x);
double funLog(double x);
double funSqr(double x);
double classicIntegral(double (*fun)(double), double a, double b, int n, int mode, std::string filename);
double trapezeIntegral(double (*fun)(double), double a, double b, int n, std::string filename);
double montecarloIntegral(double (*fun)(double), double a, double b, int n, std::string filename);
std::array <double, 2> funMaxMin(double (*fun)(double), double a, double b);
