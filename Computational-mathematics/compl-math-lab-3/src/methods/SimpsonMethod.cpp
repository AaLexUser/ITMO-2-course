//
// Created by Alexey Lapin on 4/6/23.
//

#include "SimpsonMethod.h"

SimpsonMethod::SimpsonMethod(double a, double b, double tolerance, double (*f)(double)) : IMethod(a, b, tolerance, f) {
    I0_ = solveM(a, (b - a)/n_, n_, f);
}

double SimpsonMethod::solveM(double a, double h, double n, double (*f)(double)) {
    double sum = 0;
    for (int i = 1; i < n; i++) {
        if(i % 2 == 0)
            sum += 2 * f(a + i * h);
        else
            sum += 4 * f(a + i * h);
    }
    return (sum + f(a) + f(a + n * h)) * h / 3;
}

std::pair<double, double> SimpsonMethod::solve() {
    n_ = n_ * 2;
    double h = (b_ - a_)/n_;
    double I1 = solveM(a_, h, n_, f_);
    if(abs(I0_ - I1) / 15 <= tolerance_){
        return std::make_pair(n_, I1);
    }
    I0_ = I1;
    return solve();
}
