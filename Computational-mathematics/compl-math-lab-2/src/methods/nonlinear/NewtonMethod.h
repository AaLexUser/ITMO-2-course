//
// Created by Alexey Lapin on 3/17/23.
//

#ifndef COMPLMATH2_NEWTONMETHOD_H
#define COMPLMATH2_NEWTONMETHOD_H

#include "IMethod.h"

class NewtonMethod : public IMethod{
public:
    NewtonMethod(double a, double b, double tolerance, double (*f)(double x));
    void solve() override;
private:
    double x0_;

};


#endif //COMPLMATH2_NEWTONMETHOD_H
