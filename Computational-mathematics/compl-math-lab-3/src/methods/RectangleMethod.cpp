//
// Created by Alexey Lapin on 4/5/23.
//

#include "RectangleMethod.h"

std::pair<double, double> RectangleMethod::solve() {
    n_ = n_*2;
    double h = (b_ - a_)/n_;
    double I1;
    switch (option_) {
        case 1:
            I1 = solveL(a_, h, n_, f_);
            break;
        case 2:
            I1 = solveR(a_, h, n_, f_);
            break;
        case 3:
            I1 = solveMid(a_, h, n_, f_);
            break;
    }
    if(abs(I0_ - I1) / 3 <= tolerance_){
        return std::make_pair(n_, I1);
    }
    I0_ = I1;
    return solve();
}


RectangleMethod::RectangleMethod(double a, double b, double tolerance, double (*f)(double), int option):
    IMethod(a, b, tolerance, f), option_(option){
    switch (option_) {
        case 1:
            I0_ = solveL(a_, (b_-a_)/n_, n_, f_);
            break;
        case 2:
            I0_ = solveR(a_, (b_-a_)/n_, n_, f_);
            break;
        case 3:
            I0_ = solveMid(a_, (b_-a_)/n_, n_, f_);
            break;
    }
}

double RectangleMethod::solveL(double const a, double const h, double const n, double (*f)(double)) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

double RectangleMethod::solveR(double const a, double const h, double const n, double (*f)(double)) {
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

double RectangleMethod::solveMid(double const a, double const h, double const n, double (*f)(double)) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += f(a + (i + 0.5) * h);
    }
    return sum * h;
}
