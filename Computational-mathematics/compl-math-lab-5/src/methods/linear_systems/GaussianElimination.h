//
// Created by Alexey Lapin on 4/12/23.
//

#ifndef COMPLMATH4_GAUSSIANELIMINATION_H
#define COMPLMATH4_GAUSSIANELIMINATION_H

#include<vector>
#include<cmath>
#include<iostream>
class GaussianElimination {
public:
    static std::vector<double> solve(std::vector<std::vector<double>> A, std::vector<double> b);
    static void solve(std::vector<std::vector<double>> &A, std::vector<double> &b, std::vector<double> &x);
};


#endif //COMPLMATH4_GAUSSIANELIMINATION_H
