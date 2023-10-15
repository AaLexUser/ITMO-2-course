//
// Created by Alexey Lapin on 4/6/23.
//

#ifndef COMPLMATH3_IMETHOD_H
#define COMPLMATH3_IMETHOD_H

#include <cmath>
#include <iostream>
class IMethod {
public:
    virtual std::pair<double, double> solve() = 0;
    IMethod(double a, double b, double tolerance, double (*f)(double x))
        : a_(a), b_(b), tolerance_(tolerance), f_(f){}
protected:
    double n_ = 4;
    double tolerance_;
    double a_;
    double b_;
    double (*f_)(double x);
    double I0_;
};


#endif //COMPLMATH3_IMETHOD_H
