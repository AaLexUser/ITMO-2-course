//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_LOGARITHMIC_H
#define COMPLMATH4_LOGARITHMIC_H

#include "../AbstractApproximation.h"
namespace approx {
    class Logarithmic : public AbstractApproximation {
        std::function<double(double x, std::vector<double> params)> FUNC = [](double x, std::vector<double> params) {
            return params[1] * log(x) + params[0];
        };
    public:
        explicit Logarithmic(std::vector<std::pair<double, double>> points) : AbstractApproximation(points) {
            _f = FUNC;
        }

        void fit() override;

    };
}

#endif //COMPLMATH4_LOGARITHMIC_H
