//
// Created by Alexey Lapin on 3/16/23.
//

#include "Axis.h"

void Axis::draw() {
    sf::RectangleShape line(sf::Vector2f(MainWindow::getInstance().getWindow().getSize().x, thickness_));
    line.setFillColor(sf::Color::Black);
    line.setPosition(0, MainWindow::getInstance().getY0());
    MainWindow::getInstance().getWindow().draw(line);
    line.setSize(sf::Vector2f(thickness_, MainWindow::getInstance().getWindow().getSize().y));
    line.setPosition(MainWindow::getInstance().getX0(), 0);
    MainWindow::getInstance().getWindow().draw(line);
}

std::unique_ptr<IShape> Axis::clone() const {
    return std::make_unique<Axis>(*this);
}
