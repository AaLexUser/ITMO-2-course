//
// Created by Alexey Lapin on 4/19/23.
//

#include "Logarithmic.h"
#include "Linear.h"

void approx::Logarithmic::fit() {
    auto new_points = _points;
    for(auto & point : new_points) {
        point.first = log(point.first);
    }
    Linear linear(new_points);
    linear.fit();
    auto params = linear.getParams();
    _params.push_back(params[0]);
    _params.push_back(params[1]);
    set_s();
    set_standard_deviation();
}
