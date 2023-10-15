//
// Created by Alexey Lapin on 4/12/23.
//

#include "Linear.h"

void approx::Linear::fit() {
    auto n = static_cast<double>(_points.size());
    double SX = 0, SY = 0, SXX = 0, SXY = 0;
    for(auto point : _points) {
        SX+=point.first;
        SXX+=point.first*point.first;
        SY+=point.second;
        SXY+=point.first*point.second;
    }
    std::vector<std::vector<double>> A = {{SX, SXX}, {n, SX}};
    std::vector<double> b = {SXY, SY};
    _params = std::move(GaussianElimination::solve(A, b));
    set_s();
    set_standard_deviation();
    set_pearson_correlation_coefficient();
}


void approx::Linear::set_pearson_correlation_coefficient() {
    double X = 0, Y = 0;
    for(auto point : _points) {
       X+=point.first;
       Y+=point.second;
    }
    double Sx = X / _points.size();
    double Sy = Y / _points.size();
    double Sxy = 0, Sxx = 0, Syy = 0;
    for(auto point : _points) {
        Sxy += (point.first - Sx)*(point.second - Sy);
        Sxx += (point.first - Sx)*(point.first - Sx);
        Syy += (point.second - Sy)*(point.second - Sy);
    }
    _extras["Pearson Correlation Coefficient"] = Sxy / sqrt(Sxx*Syy);
}










