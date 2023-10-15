//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_BESSELINTERPOLATION_H
#define COMPLMATH5_BESSELINTERPOLATION_H


#include "Interpolation.h"

class BesselInterpolation : public Interpolation{
public:
    double predict(const std::vector<std::pair<double, double>> &points, const double arg) override;
    std::string getFunctionAsString(const std::vector<std::pair<double, double>> &points) override;
private:
    double _tcal(float t, int n);
    std::string _tcalStr(std::string t, int n);
};


#endif //COMPLMATH5_BESSELINTERPOLATION_H
