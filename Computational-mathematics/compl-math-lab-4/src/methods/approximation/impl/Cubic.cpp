//
// Created by Alexey Lapin on 4/19/23.
//

#include "Cubic.h"

void approx::Cubic::fit() {
    auto n = static_cast<double>(_points.size());
    std::vector<std::vector<double>> A(4);
    for(int i = 0; i < A.size(); i++) {
        A[i].push_back(pair_sum(_points, i));
        A[i].push_back(pair_sum(_points, i+1));
        A[i].push_back(pair_sum(_points, i+2));
        A[i].push_back(pair_sum(_points, i+3));
    }
    std::vector<double> b(4);
    for(int i = 0; i < b.size(); i++) {
        b[i] = two_pair_sum(_points, i, 1);
    }
    _params = std::move(GaussianElimination::solve(A, b));
    set_s();
    set_standard_deviation();

}
