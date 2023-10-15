//
// Created by Alexey Lapin on 4/25/23.
//

#include "NewtonPolynomial.h"

double interpolate_model::NewtonPolynomial::predict(const std::vector<std::pair<double, double>> & points, const double arg) {
    auto mid = points[points.size()/2].first;
    if(arg < mid){
        return forwardInterpolation(points, arg);
    } else {
        return backwardInterpolation(points, arg);
    }
}

double interpolate_model::NewtonPolynomial::forwardInterpolation(const std::vector<std::pair<double, double>> &points,
                                                                 const double arg) {
    double h = (points.back().first - points.front().first) / (points.size()-1);
    auto it = std::lower_bound(
            points.begin(), points.end(), arg, [](const std::pair<double, double> &a, const double &b) {
                return a.first < b;
            }
    );
    size_t xIndex = std::prev(it) - points.begin();
    double t = (arg - points[xIndex].first) / h;
    Math::calculateFinalDifferencesMatrix(points, _finalDifferencesMatrix);
    std::vector<double>& delta = (Math::T(_finalDifferencesMatrix))[xIndex];
    double res = 0;
    for(int i = 0; i < delta.size(); ++i){
        double P = 1;
        for(int j = 0; j < i; ++j){
            P*= (t - j) / (i - j);
        }
        res+= delta[i]*P;
    }
    Math::T(_finalDifferencesMatrix);
    return res;
}

double interpolate_model::NewtonPolynomial::backwardInterpolation(const std::vector<std::pair<double, double>> &points,
                                                                  const double arg) {
    double h = (points.back().first - points.front().first) / (points.size()-1);
    auto it = std::lower_bound(
            points.begin(), points.end(), arg, [](const std::pair<double, double> &a, const double &b) {
                return a.first < b;
            }
    );
    size_t xIndex = it - points.begin();
    double t = (arg - points[xIndex].first) / h;
    Math::calculateFinalDifferencesMatrix(points, _finalDifferencesMatrix);
    double res = 0;
    for(int i = 0; i < _finalDifferencesMatrix[0].size(); ++i){
        double P = 1;
        for(int j = 0; j < i; ++j){
            P*= (t + j) / (i - j);
        }
        res+= _finalDifferencesMatrix[i][xIndex-i]*P;
    }
    return res;
}

std::string
interpolate_model::NewtonPolynomial::getFunctionAsString(const std::vector<std::pair<double, double>> &points) {
    std::string res = "";
    double h =(points.back().first - points.front().first) / (points.size()-1);
    Math::calculateFinalDifferencesMatrix(points, _finalDifferencesMatrix);
    for(int i = 0; i < _finalDifferencesMatrix[0].size(); ++i){
        std::string temp = "";
        for(int j = 0; j < i; ++j){
            temp+= "(x - " + std::to_string(points[j].first) + ")" + (j != i-1 || i == 1 ? " * " : "");
        }
        if(i > 1){
            temp = "("  + temp + ")" + " * ";
        }
        res+= temp + "("
                + std::to_string(_finalDifferencesMatrix[i][0]/(Math::factorial(i)*pow(h, i))) + ")";
        if(i != _finalDifferencesMatrix[0].size()-1){
            res+= " + ";
        }
    }
    return res;
}
