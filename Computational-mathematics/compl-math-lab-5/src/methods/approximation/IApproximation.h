//
// Created by Alexey Lapin on 4/13/23.
//

#ifndef COMPLMATH4_IAPPROXIMATION_H
#define COMPLMATH4_IAPPROXIMATION_H

#include <vector>
#include <cmath>
#include <iostream>
#include "../../utils/out/CTable.h"
#include "../linear_systems/GaussianElimination.h"
#include "../../utils/math/Matrix.h"
namespace approx {
    class IApproximation {
    public:
        virtual ~IApproximation() = default;

        virtual void fit() = 0;

        virtual std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> get_info() = 0;

        virtual double get_extra_info(std::string key) = 0;

        virtual std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> get_extras_info() = 0;

        virtual const std::function<double(double, std::vector<double>)> &getF() const = 0;

        virtual const std::vector<double> &getParams() const = 0;

    private:
        virtual void set_s() = 0;

        virtual void set_standard_deviation() = 0;

    };
}

#endif //COMPLMATH4_IAPPROXIMATION_H
