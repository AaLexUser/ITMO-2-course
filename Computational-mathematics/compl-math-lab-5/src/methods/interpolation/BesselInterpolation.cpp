//
// Created by Alexey Lapin on 4/26/23.
//

#include "BesselInterpolation.h"

double BesselInterpolation::predict(const std::vector<std::pair<double, double>> &points, const double arg) {
    Math::calculateFinalDifferencesMatrix(points, _finalDifferencesMatrix);
    int k;
    if (points.size() % 2) // origin for odd
        k = points.size() / 2;
    else
        k = points.size() / 2 - 1; // origin for even
    float sum = (_finalDifferencesMatrix[0][k] + _finalDifferencesMatrix[0][k+1]) / 2;
    float t = (arg - points[k].first) / (points[1].first - points[0].first);
    for (int i = 1; i < points.size(); i++) {
        if (i % 2)
            sum = sum + ((t - 0.5) *
                         _tcal(t, i - 1) * _finalDifferencesMatrix[i][k]) / Math::factorial(i);
        else
            sum = sum + (_tcal(t, i) *
                         (_finalDifferencesMatrix[i][k] + _finalDifferencesMatrix[i][--k]) / (Math::factorial(i) * 2));
    }
    return sum;
}

double BesselInterpolation::_tcal(float t, int n) {
    if (n == 0)
        return 1;

    float temp = t;
    for (int i = 1; i <= n / 2; i++)
        temp = temp * (t - i);

    for (int i = 1; i < n / 2; i++)
        temp = temp * (t + i);

    return temp;
}

std::string BesselInterpolation::getFunctionAsString(const std::vector<std::pair<double, double>> &points) {
    int k;
    if (points.size() % 2) // origin for odd
        k = points.size() / 2;
    else
        k = points.size() / 2 - 1; // origin for even
    std::string t = "( ( x - ( " + std::to_string(points[k].first) + ") )/(" + std::to_string(points[1].first - points[0].first) + ") )";
    std::string sum = std::to_string((_finalDifferencesMatrix[0][k] + _finalDifferencesMatrix[0][k+1]) / 2);
    for (int i = 1; i < points.size(); i++) {
        if (i % 2)
            sum += " + ( (" + t + " -  0.5)" +
                    _tcalStr(t, i - 1) + " * " + "( " + std::to_string(_finalDifferencesMatrix[i][k]) + ")  ) / " +
                    std::to_string(Math::factorial(i));
        else
            sum += " + ( " + _tcalStr(t, i) + " * (" +
                         std::to_string((_finalDifferencesMatrix[i][k] + _finalDifferencesMatrix[i][--k]) ) + ") )" +
                         " / (" + std::to_string(Math::factorial(i) * 2) + ")";
    }
    return sum;
}

std::string BesselInterpolation::_tcalStr(std::string t, int n) {
    if (n == 0)
        return "";
    std::string temp = t;
    for (int i = 1; i <= n / 2; i++)
        temp += " * " "( " + t + " - " + std::to_string(i) + " )";

    for (int i = 1; i < n / 2; i++)
        temp += " * " "( " + t + " + " + std::to_string(i) + " )";

    return temp;
}
