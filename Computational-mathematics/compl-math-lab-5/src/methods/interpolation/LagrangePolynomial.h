//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_LAGRANGEPOLYNOMIAL_H
#define COMPLMATH5_LAGRANGEPOLYNOMIAL_H

#include <vector>
#include <iostream>
#include "Interpolation.h"

namespace interpolate_model {
    class LagrangePolynomial : Interpolation {
        public:
            double predict(const std::vector<std::pair<double, double>> & points, const double arg) override;
            std::string getFunctionAsString(const std::vector<std::pair<double, double>> &points);
    };

}

#endif //COMPLMATH5_LAGRANGEPOLYNOMIAL_H
