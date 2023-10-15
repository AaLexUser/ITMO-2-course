//
// Created by Alexey Lapin on 4/19/23.
//

#include "Points.h"

void Points::draw() {
    sf::VertexArray pointsArray(sf::PrimitiveType::Points);
   for (auto & point : points_) {
        float x = MainWindow::getInstance().getX0() + point.first * MainWindow::getInstance().getScale();
        float y = MainWindow::getInstance().getY0() - point.second * MainWindow::getInstance().getScale();
        sf::CircleShape circle(radius_);
        // Set the position and color of the circle
        circle.setPosition(x - circle.getRadius(), y - circle.getRadius());
        circle.setFillColor(color_);
        // Draw the circle to the window
        MainWindow::getInstance().getWindow().draw(circle);
    }
}

Points::Points(const std::vector<std::pair<double, double>> & points, sf::Color color, double radius)
: points_(points), color_(color), radius_(radius) {}

std::unique_ptr<IShape> Points::clone() const {
    return std::make_unique<Points>(*this);
}
