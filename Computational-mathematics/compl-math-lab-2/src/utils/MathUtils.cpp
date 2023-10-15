//
// Created by Alexey Lapin on 3/17/23.
//

#include "MathUtils.h"

double MathUtils::derivative(double (*pFunction)(double), double x, double h) {
    return (pFunction(x + h) - pFunction(x)) / h;
}
double MathUtils::secondDerivative(double (*pFunction)(double), double x, double h) {
    return (derivative(pFunction, (x + h)) - derivative(pFunction, x) )/ h;
}
double MathUtils::partialDerivative(double (*f)(double, double), double x, double y, double h, bool wrt_x) {
    if (wrt_x) {
        return (f(x + h, y) - f(x, y)) / h;
    } else {
        return (f(x, y + h) - f(x, y)) / h;
    }
}