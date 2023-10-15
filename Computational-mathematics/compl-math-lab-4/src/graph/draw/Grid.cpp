//
// Created by Alexey Lapin on 3/16/23.
//

#include "Grid.h"

void Grid::draw() {
    sf::RectangleShape line(sf::Vector2f(MainWindow::getInstance().getWindow().getSize().x, thickness_));
    line.setFillColor(sf::Color::Black);
    for (int i = 0; i < MainWindow::getInstance().getWindow().getSize().y; i += MainWindow::getInstance().getScale()) {
        line.setPosition(0, i + MainWindow::getInstance().getY0());
        MainWindow::getInstance().getWindow().draw(line);
        line.setPosition(0,  MainWindow::getInstance().getY0() - i);
        MainWindow::getInstance().getWindow().draw(line);
    }
    line.setSize(sf::Vector2f(thickness_, MainWindow::getInstance().getWindow().getSize().y));
    for (int i = 0; i < MainWindow::getInstance().getWindow().getSize().x; i += MainWindow::getInstance().getScale()) {
        line.setPosition(i + MainWindow::getInstance().getX0(), 0);
        MainWindow::getInstance().getWindow().draw(line);
        line.setPosition(MainWindow::getInstance().getX0() - i, 0);
        MainWindow::getInstance().getWindow().draw(line);
    }
}

std::unique_ptr<IShape> Grid::clone() const {
    return std::make_unique<Grid>(*this);
}
