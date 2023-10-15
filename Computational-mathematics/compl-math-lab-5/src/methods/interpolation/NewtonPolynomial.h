//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_NEWTONPOLYNOMIAL_H
#define COMPLMATH5_NEWTONPOLYNOMIAL_H


#include "Interpolation.h"
namespace interpolate_model {
    class NewtonPolynomial : public Interpolation {
    public:
        double predict(const std::vector<std::pair<double, double>> & points, const double arg) override;
        std::string getFunctionAsString(const std::vector<std::pair<double, double>> & points);
    private:
        double forwardInterpolation(const std::vector<std::pair<double, double>> & points, const double arg);
        double backwardInterpolation(const std::vector<std::pair<double, double>> & points, const double arg);
    };
}

#endif //COMPLMATH5_NEWTONPOLYNOMIAL_H
