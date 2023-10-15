//
// Created by Alexey Lapin on 3/17/23.
//

#include "AxisNumbers.h"

void AxisNumbers::draw() {
    sf::Font font;
    if (!font.loadFromFile("/Users/aleksejlapin/CLionProjects/ComplMath4/Roboto/Roboto-Regular.ttf")) {
        throw std::runtime_error("Can't load font");
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(0.5 * MainWindow::getInstance().getScale());
    text.setFillColor(sf::Color::Black);
    MainWindow::getInstance().getWindow().draw(text);
    text.setPosition(MainWindow::getInstance().getX0() - MainWindow::getInstance().getScale() / 3, MainWindow::getInstance().getY0() + 0.3 * MainWindow::getInstance().getScale());
    text.setString("0");
    MainWindow::getInstance().getWindow().draw(text);
    for (int i = 1; i < MainWindow::getInstance().getWindow().getSize().x / MainWindow::getInstance().getScale(); i++) {
        text.setPosition(MainWindow::getInstance().getX0() + i * MainWindow::getInstance().getScale() - 0.2 * MainWindow::getInstance().getScale(),
                         MainWindow::getInstance().getY0() + 0.3 * MainWindow::getInstance().getScale());
        text.setString(std::to_string(i));
        MainWindow::getInstance().getWindow().draw(text);
        text.setPosition(MainWindow::getInstance().getX0() - i * MainWindow::getInstance().getScale() - 0.2 * MainWindow::getInstance().getScale(), MainWindow::getInstance().getY0() + 0.3 * MainWindow::getInstance().getScale());
        text.setString(std::to_string(-i));
        MainWindow::getInstance().getWindow().draw(text);
    }
    for (int i = 1; i < MainWindow::getInstance().getWindow().getSize().y / MainWindow::getInstance().getScale(); i++) {
        text.setPosition(MainWindow::getInstance().getX0() + 0.2 * MainWindow::getInstance().getScale(), MainWindow::getInstance().getY0() + i * MainWindow::getInstance().getScale());
        text.setString(std::to_string(-i));
        MainWindow::getInstance().getWindow().draw(text);
        text.setPosition(MainWindow::getInstance().getX0() + 0.2 * MainWindow::getInstance().getScale(), MainWindow::getInstance().getY0() - i * MainWindow::getInstance().getScale());
        text.setString(std::to_string(i));
        MainWindow::getInstance().getWindow().draw(text);
    }

}

std::unique_ptr<IShape> AxisNumbers::clone() const {
    return std::make_unique<AxisNumbers>(*this);
}
