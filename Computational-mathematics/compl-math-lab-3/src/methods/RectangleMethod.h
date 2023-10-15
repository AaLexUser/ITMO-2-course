//
// Created by Alexey Lapin on 4/5/23.
//

#ifndef COMPLMATH3_RECTANGLEMETHOD_H
#define COMPLMATH3_RECTANGLEMETHOD_H

#include "IMethod.h"

class RectangleMethod : public IMethod{
public:
    RectangleMethod(double a, double b, double tolerance, double (*f)(double x), int option);
    std::pair<double, double> solve() override;
private:
    static double solveL(double a,  double h, double n, double (*f)(double x));
    static double solveR(double a, double h, double n, double (*f)(double));
    static double solveMid(double a, double h, double n, double (*f)(double));
    int option_;
};


#endif //COMPLMATH3_RECTANGLEMETHOD_H
