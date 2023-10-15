//
// Created by Alexey Lapin on 4/6/23.
//

#include "TrapezoidMethod.h"

TrapezoidMethod::TrapezoidMethod(double a, double b, double tolerance, double (*f)(double)) : IMethod(a, b, tolerance, f)
{
    I0_ = solveM(a, (b - a)/n_, n_, f);
}

std::pair<double, double> TrapezoidMethod::solve() {
    n_ = n_*2;
    double h = (b_ - a_)/n_;
    double I1 = solveM(a_, h, n_, f_);
    if(abs(I0_ - I1) / 3 <= tolerance_){
        return std::make_pair(n_, I1);
    }
    I0_ = I1;
    return solve();
}

double TrapezoidMethod::solveM(double a, double h, double n, double (*f)(double)) {
    double sum = 0;
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return (sum + (2 * a + n * h) / 2)  * h;
}
