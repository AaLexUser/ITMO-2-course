//
// Created by Alexey Lapin on 4/6/23.
//

#ifndef COMPLMATH3_TRAPEZOIDMETHOD_H
#define COMPLMATH3_TRAPEZOIDMETHOD_H

#include "IMethod.h"
class TrapezoidMethod : public IMethod{
public:
    TrapezoidMethod(double a, double b, double tolerance, double (*f)(double x));
    std::pair<double, double> solve() override;
private:
    static double solveM(double a, double h, double n, double (*f)(double));
};


#endif //COMPLMATH3_TRAPEZOIDMETHOD_H
