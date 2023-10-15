//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_STIRLINGSCHEME_H
#define COMPLMATH5_STIRLINGSCHEME_H

#include "Interpolation.h"

class StirlingScheme : public Interpolation{
public:
    double predict(const std::vector<std::pair<double, double>> &points, const double arg) override;
    std::string getFunctionAsString(const std::vector<std::pair<double, double>> &points) override;
};


#endif //COMPLMATH5_STIRLINGSCHEME_H
