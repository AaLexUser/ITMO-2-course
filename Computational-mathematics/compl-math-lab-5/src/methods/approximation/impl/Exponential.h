//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_EXPONENTIAL_H
#define COMPLMATH4_EXPONENTIAL_H

#include "../AbstractApproximation.h"
//#include "Linear.h"
namespace approx {
    class Exponential : public AbstractApproximation {
        std::function<double(double x, std::vector<double> params)> FUNC = [](double x, std::vector<double> params) {
            return params[0] * exp(params[1] * x);
        };
    public:
        explicit Exponential(std::vector<std::pair<double, double>> points) : AbstractApproximation(points) {
            _f = FUNC;
        }

        void fit() override;

    };
}


#endif //COMPLMATH4_EXPONENTIAL_H
