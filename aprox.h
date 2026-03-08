//
// Created by jds on 3/4/26.
//
#pragma once

double funSin(double x);
double funExp(double x);
double funLog(double x);
double funSqr(double x);
double classicIntegral(double (*fun)(double), double a, double b, int n, int mode, std::string filename);
