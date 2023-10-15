//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_POWER_H
#define COMPLMATH4_POWER_H

#include "../AbstractApproximation.h"
namespace approx {
    class Power : public AbstractApproximation {
        std::function<double(double x, std::vector<double> params)> FUNC = [](double x, std::vector<double> params) {
            return params[0] * pow(x, params[1]);
        };
    public:
        explicit Power(std::vector<std::pair<double, double>> points) : AbstractApproximation(points) {
            _f = FUNC;
        }

        void fit() override;

    };
}


#endif //COMPLMATH4_POWER_H
