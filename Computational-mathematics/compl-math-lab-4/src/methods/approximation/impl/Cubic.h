//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_CUBIC_H
#define COMPLMATH4_CUBIC_H

#include "../AbstractApproximation.h"

namespace approx {
    class Cubic : public AbstractApproximation {
        std::function<double(double x, std::vector<double> params)> FUNC = [](double x, std::vector<double> params) {
            return params[3] * x * x * x + params[2] * x * x + params[1] * x + params[0];
        };
    public:
        explicit Cubic(std::vector<std::pair<double, double>> points) : AbstractApproximation(points) {
            _f = FUNC;
        }

        void fit() override;
    };
}
#endif //COMPLMATH4_CUBIC_H
