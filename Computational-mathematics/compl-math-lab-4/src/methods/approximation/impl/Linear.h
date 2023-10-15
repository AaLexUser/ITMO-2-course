//
// Created by Alexey Lapin on 4/12/23.
//

#ifndef COMPLMATH4_LINEAR_H
#define COMPLMATH4_LINEAR_H

#include "../AbstractApproximation.h"
namespace approx {
    class Linear : public AbstractApproximation {
        std::function<double(double x, std::vector<double> params)> FUNC = [](double x, std::vector<double> params) {
            return params[1] * x + params[0];
        };
    public:
        explicit Linear(std::vector<std::pair<double, double>> points) : AbstractApproximation(points) {
            _f = FUNC;
        }

        void fit() override;

    private:
        void set_pearson_correlation_coefficient();
    };
}

#endif //COMPLMATH4_LINEAR_H
