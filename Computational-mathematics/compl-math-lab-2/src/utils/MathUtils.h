//
// Created by Alexey Lapin on 3/17/23.
//

#ifndef COMPLMATH2_MATHUTILS_H
#define COMPLMATH2_MATHUTILS_H


class MathUtils {
    public:
    static double derivative(double (*pFunction)(double), double x, double h = 1e-5);
    static double secondDerivative(double (*f)(double), double x, double h = 1e-5);
    static double partialDerivative(double (*f)(double, double), double x, double y, double h = 1e-5, bool wrt_x = true);
};


#endif //COMPLMATH2_MATHUTILS_H
