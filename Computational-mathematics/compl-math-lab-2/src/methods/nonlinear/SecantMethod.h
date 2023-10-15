//
// Created by Alexey Lapin on 3/17/23.
//

#ifndef COMPLMATH2_SECANTMETHOD_H
#define COMPLMATH2_SECANTMETHOD_H


#include "IMethod.h"

class SecantMethod : public IMethod{
public:
    SecantMethod(double a, double b, double tolerance, double (*f)(double x));
    void solve() override;
private:

    double x0_;
    double x1_;
};


#endif //COMPLMATH2_SECANTMETHOD_H
