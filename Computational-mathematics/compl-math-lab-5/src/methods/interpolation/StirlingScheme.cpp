//
// Created by Alexey Lapin on 4/26/23.
//

#include "StirlingScheme.h"

double StirlingScheme::predict(const std::vector<std::pair<double, double>> &points, const double arg) {
    std::vector<std::pair<double, double>> pointsCopy = points;
    double h = (points.back().first - points.front().first) / (points.size()-1);
    auto itr = std::lower_bound(
            points.begin(), points.end(), arg, [](const std::pair<double, double> &a, const double &b) {
                return a.first < b;
            }
    );
    auto itl = std::prev(itr) == points.begin() ? points.begin() : std::prev(itr);
    if(itr == points.end()){
        itr = std::prev(itr);
        itl = std::prev(itr);
    }
    size_t x0Index;
    if(itr->first - arg > arg - itl->first ){
        x0Index = itl - points.begin();
    }
    else{
        x0Index = itr - points.begin();
    }
    if(points.size() % 2 == 0){
        if(x0Index >= points.size() / 2){
            std::erase(pointsCopy, pointsCopy.front());
            x0Index--;
        }
        else std::erase(pointsCopy, pointsCopy.back());
    }
    double t = (arg - pointsCopy[x0Index].first) / h;
    Math::calculateFinalDifferencesMatrix(pointsCopy, _finalDifferencesMatrix);
    double res = 0;
    std::vector<double> fact = Math::createFactorial<double>(pointsCopy.size());
    res+= _finalDifferencesMatrix[0][x0Index];
    for(int i = 1; i <= x0Index; ++i){
        double P = 1;
        for(int j = 1; j < i-1; ++j){
            P*= (pow(t,2) - pow(j,2));
        }
        res+= 1.0 / fact[2 * i - 1] * P * t * (_finalDifferencesMatrix[2 * i - 1][ 1 - i + x0Index]
                + _finalDifferencesMatrix[2 * i - 1][ - i + x0Index]) / 2;
        res += 1.0 / fact[2 * i] * P * pow(t, 2) * _finalDifferencesMatrix[2 * i][ - i + x0Index];
    }
    return res;
}

std::string StirlingScheme::getFunctionAsString(const std::vector<std::pair<double, double>> &points) {
    std::string res = "";
    double h =(points.back().first - points.front().first) / (points.size()-1);
    std::vector<std::pair<double, double>> pointsCopy = points;
    if(points.size() % 2 == 0){
        std::erase(pointsCopy, pointsCopy.front());
    }
    int x0Index = ceil(pointsCopy.size() / 2) ;
    Math::calculateFinalDifferencesMatrix(pointsCopy, _finalDifferencesMatrix);
    std::vector<double> fact = Math::createFactorial<double>(pointsCopy.size());
    res+= std::to_string(_finalDifferencesMatrix[0][0]);
    auto t = "( x - ( " + std::to_string(points[x0Index].first) + ") ) / " + "(" + std::to_string(h) + ") ";
    for(int i = 1; i <= x0Index; ++i){
        std::string P = "";
        for(int j = 1; j < i-1; ++j){
            P+= "((" + t + ")^2 - " + "(" + std::to_string(j) + ")" + "^2)" + (j == i-2 ? "" : "*");
        }
        res+= " + ( " + std::to_string(1.0 / fact[2 * i - 1]) + " )";
        if(!P.empty()) res+= " * ( " + P + " )" ;
        res +=  " * ( " +  t + "  ) * (";
        res += "( " + std::to_string(_finalDifferencesMatrix[2 * i - 1][ 1 - i + x0Index] + _finalDifferencesMatrix[2 * i - 1][ - i + x0Index]) + " )" ;
        res += ") / 2";
        res += " + ( " + std::to_string(1.0 / fact[2 * i]) + " )";
        if(!P.empty()) res+= " * ( " + P + " )";
        res += " * ( " +  t + "  )^2 * ";
        res += "( " + std::to_string(_finalDifferencesMatrix[2 * i][ - i + x0Index]) + " )" ;
    }
    return res;
}
