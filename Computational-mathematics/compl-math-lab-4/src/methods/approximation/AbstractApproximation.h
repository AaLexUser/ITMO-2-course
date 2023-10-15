//
// Created by Alexey Lapin on 4/13/23.
//

#ifndef COMPLMATH4_ABSTRACTAPPROXIMATION_H
#define COMPLMATH4_ABSTRACTAPPROXIMATION_H

#include <utility>

#include "IApproximation.h"
namespace approx {
    class AbstractApproximation : public IApproximation {
    protected:
        explicit AbstractApproximation(std::vector<std::pair<double, double>> points) : _points(std::move(points)) {}

        AbstractApproximation(const std::function<double(double, std::vector<double>)> &f,
                              const std::vector<std::pair<double, double>> &points);


    public:
        std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> get_info() override;

        double get_extra_info(std::string key) override;

        std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> get_extras_info() override;

        [[nodiscard]] const std::function<double(double, std::vector<double>)> &getF() const override;

        const std::vector<double> &getParams() const override;

    protected:
        std::function<double(double x, std::vector<double> params)> _f;
        std::vector<std::pair<double, double>> _points;
        std::vector<double> _params;
        std::unordered_map<std::string, double> _extras;
    protected:
        void set_s() override;

        void set_standard_deviation() override;

        double pair_sum(const std::vector<std::pair<double, double>> array, int powNum = 1, bool choice = true) const;

        double two_pair_sum(const std::vector<std::pair<double, double>> array, int powNum1 = 1, int powNum2 = 1) const;

    };
}

#endif //COMPLMATH4_ABSTRACTAPPROXIMATION_H
