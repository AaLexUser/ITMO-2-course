//
// Created by Alexey Lapin on 4/25/23.
//

#include "LagrangePolynomial.h"

double interpolate_model::LagrangePolynomial::predict(const std::vector<std::pair<double, double>> & points, const double arg) {
    double L = 0;
    for(int i = 0; i < points.size(); ++i){
        double P = 1;
        for(int j = 0; j < points.size(); ++j){
            if(j != i){
                P*= (arg - points[j].first) / (points[i].first - points[j].first);
            }
        }
        L+= points[i].second*P;
    }
    return L;
}

std::string interpolate_model::LagrangePolynomial::getFunctionAsString(const std::vector<std::pair<double, double>> &points) {
    std::string res = "";
    for(int i = 0; i < points.size(); ++i){
        std::string P = "";
        for(int j = 0; j < points.size(); ++j){
            if(j != i){
                P+= " * (x - " + std::to_string(points[j].first) + ")/(" + std::to_string(points[i].first) + " - " + std::to_string(points[j].first) + ")";
            }
        }
        res+= std::to_string(points[i].second)  + P + " + ";
    }
    return res.substr(0, res.size() - 3);
}
