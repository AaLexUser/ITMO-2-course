//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_POINTS_H
#define COMPLMATH5_POINTS_H

#include <set>

class Points {
    std::set<double> arrayX;
    std::multiset<double> arrayY;
public:
    void insert(double x, double y){
        arrayX.emplace(x);
        arrayY.emplace(y);
    }


};


#endif //COMPLMATH5_POINTS_H
