//
// Created by Alexey Lapin on 3/23/23.
//

#include <stdexcept>
#include "Validator.h"

bool Validator::validateExistanceOfRoots(double x0, double y0, double (*f)(double)) {
    if (isnan(f(x0))|| isnan(f(y0)))
        throw std::runtime_error("Function is not defined in the given interval");
    if(isinf(f(x0)) || isinf(f(y0)))
        std::throw_with_nested("Function is go to infinity in the given interval");
    return f(x0)*f(y0) < 0;
}

bool
Validator::validateUniquenessOfRoots(double x0, double y0, double (*f)(double)) {
    return  validateMonotonicity(x0, y0, f) && validateExistanceOfRoots(x0,y0, f);
}

bool Validator::validateMonotonicity(double x0, double y0, double (*f)(double)) {
    double c = (y0-x0) / 100;
    for(int i = 1; i < 100; i++){
        if(MathUtils::derivative(f,x0,1e-2) * MathUtils::derivative(f,x0+c,1e-2) < 0)
            throw std::runtime_error("Function is not monotonic in the given interval");
        else x0 = x0+c;
    }
    return true;
}
