//
// Created by Alexey Lapin on 4/6/23.
//

#ifndef COMPLMATH3_SIMPSONMETHOD_H
#define COMPLMATH3_SIMPSONMETHOD_H


#include "IMethod.h"

class SimpsonMethod : public IMethod {
public:
    SimpsonMethod(double a, double b, double tolerance, double (*f)(double x));
    std::pair<double, double> solve() override;
private:
    static double solveM(double a, double h, double n, double (*f)(double));
};


#endif //COMPLMATH3_SIMPSONMETHOD_H
