//
// Created by Alexey Lapin on 3/18/23.
//

#ifndef COMPLMATH2_NEWTONSYSTEMMETHOD_H
#define COMPLMATH2_NEWTONSYSTEMMETHOD_H


#include "ISystemMethod.h"

class NewtonSystemMethod : ISystemMethod {
    public:
        NewtonSystemMethod(double x0, double y0, double tolerance, double (*f) (double, double),
                           double (*g) (double, double));
        void solve() override;
private:
    double dxf;
    double dyf;
    double dxg;
    double dyg;
    double a[2][2];
    double b[2];

};


#endif //COMPLMATH2_NEWTONSYSTEMMETHOD_H
