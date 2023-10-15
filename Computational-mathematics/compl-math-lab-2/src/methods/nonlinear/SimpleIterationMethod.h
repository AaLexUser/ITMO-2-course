//
// Created by Alexey Lapin on 3/17/23.
//

#ifndef COMPLMATH2_SIMPLEITERATIONMETHOD_H
#define COMPLMATH2_SIMPLEITERATIONMETHOD_H


#include "IMethod.h"

class SimpleIterationMethod : public IMethod{
public:
    SimpleIterationMethod(double a, double b, double tolerance, double (*f)(double x));
    void solve() override;
private:
    static double phi(double, double, double (*)(double));
    double sigma_;
    double x0_;
};


#endif //COMPLMATH2_SIMPLEITERATIONMETHOD_H
