//
// Created by Alexey Lapin on 3/23/23.
//

#ifndef COMPLMATH2_VALIDATOR_H
#define COMPLMATH2_VALIDATOR_H
#include "../utils/MathUtils.h"
#include <cmath>

class Validator {
public:
    static bool validateExistanceOfRoots(double x0, double y0, double (*f) (double));

    static bool validateUniquenessOfRoots(double x0, double y0, double (*f) (double));

    static bool  validateMonotonicity(double x0, double y0, double (*f) (double));
};


#endif //COMPLMATH2_VALIDATOR_H
