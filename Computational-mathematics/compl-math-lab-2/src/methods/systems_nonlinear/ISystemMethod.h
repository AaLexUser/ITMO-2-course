//
// Created by Alexey Lapin on 3/18/23.
//

#ifndef COMPLMATH2_ISYSTEMMETHOD_H
#define COMPLMATH2_ISYSTEMMETHOD_H
#include <cmath>
#include <iostream>
#include "../../utils/MathUtils.h"
class ISystemMethod {
    public:
        explicit ISystemMethod(double x0, double y0, double tolerance, double (*f) (double, double),
                               double (*g) (double, double))
            : x0_(x0), y0_(y0), tolerance_(tolerance), f_(f), g_(g) {}
        virtual void solve() = 0;
        virtual ~ISystemMethod() {
            delete[] roots_;
        };
    protected:
        unsigned int counter_ = 0;
        double x0_;
        double y0_;
        double tolerance_;
        double (*f_) (double, double);
        double (*g_) (double, double);
        double * roots_ = new double[2];
};
#endif //COMPLMATH2_ISYSTEMMETHOD_H
