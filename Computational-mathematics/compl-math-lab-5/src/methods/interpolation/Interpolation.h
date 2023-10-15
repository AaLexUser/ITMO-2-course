//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_INTERPOLATION_H
#define COMPLMATH5_INTERPOLATION_H
#include <vector>
#include <iostream>
#include "../../utils/math/Math.h"
class Interpolation {
public:
    virtual ~Interpolation() =  default;
    virtual double predict(const std::vector<std::pair<double, double>> & points, const double arg) = 0;
    virtual std::string getFunctionAsString(const std::vector<std::pair<double, double>> &points) = 0;
protected:
    std::vector<std::vector<double>> _finalDifferencesMatrix;
};

#endif //COMPLMATH5_INTERPOLATION_H
