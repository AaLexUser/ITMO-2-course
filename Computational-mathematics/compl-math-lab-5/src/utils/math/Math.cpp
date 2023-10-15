//
// Created by Alexey Lapin on 4/25/23.
//

#include "Math.h"

void Math::calculateFinalDifferencesMatrix(const std::vector<std::pair<double, double>> &vec, std::vector<std::vector<double>> & res) {
    std::vector<double> temp;
    temp.reserve(vec.size());
    for (const auto &[first, second] : vec) {
        temp.push_back(trunc(second*10e5)/10e5);
    }
    res.push_back(temp);
    for(int y = 1; y < vec.size(); res.push_back(temp), ++y) {
        calculateFinalDifferences(temp, y-1);
    }
}

std::vector<double> &Math::calculateFinalDifferences(std::vector<double> &vec, int k) {
    for (auto it = vec.begin(), next = std::next(it); next != (vec.end()-k); ++it, ++next) {
        *it = *next - *it;
    }
    for(auto it = vec.end()-k-1; it != vec.end(); ++it){
        *it = 0;
    }
    return vec;
}
