//
// Created by Alexey Lapin on 4/19/23.
//

#include "Quadratic.h"

void approx::Quadratic::fit() {
    auto n = static_cast<double>(_points.size());
    double SX = 0, S2X = 0, S3X=0, S4X = 0,  SY = 0, SXY = 0, S2XY = 0;
    for(auto point : _points) {
        SX+=point.first;
        S2X+=point.first*point.first;
        S3X+=point.first*point.first*point.first;
        S4X+=point.first*point.first*point.first*point.first;
        SY+=point.second;
        SXY+=point.first*point.second;
        S2XY+=point.first*point.first*point.second;
    }
    std::vector<std::vector<double>> A = {{n, SX, S2X}, {SX, S2X, S3X}, {S2X, S3X, S4X}};
    std::vector<double> b = {SY, SXY, S2XY};
    _params = std::move(GaussianElimination::solve(A, b));
    set_s();
    set_standard_deviation();
}
