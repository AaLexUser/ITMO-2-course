//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_POINTS_H
#define COMPLMATH4_POINTS_H


#include "AbstractShape.h"

class Points : public AbstractShape{
public:
    Points(const std::vector<std::pair<double, double>> &, sf::Color color = sf::Color::Black, double radius = 10);
    void draw() override;
    [[nodiscard]] std::unique_ptr<IShape> clone() const override;
private:
    std::vector<std::pair<double, double>> points_;
    sf::Color color_;
    double radius_;
};


#endif //COMPLMATH4_POINTS_H
