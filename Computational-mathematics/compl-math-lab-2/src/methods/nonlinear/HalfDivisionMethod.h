//
// Created by Alexey Lapin on 3/9/23.
//

#ifndef INC_2_HALFDIVISIONMETHOD_H
#define INC_2_HALFDIVISIONMETHOD_H

#include "IMethod.h"
struct HalfDivisionMethod : public IMethod {
    HalfDivisionMethod(double a, double b, double tolerance ,double (*f)(double x)) :
                                                 IMethod(a, b, f, tolerance) {
        counter++;
    }
    void solve() override;
};
#endif //INC_2_HALFDIVISIONMETHOD_H