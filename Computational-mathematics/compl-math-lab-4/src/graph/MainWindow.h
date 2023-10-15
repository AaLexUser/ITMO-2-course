//
// Created by Alexey Lapin on 3/6/23.
//

#ifndef INC_2_GRAPH_H
#define INC_2_GRAPH_H

#include <SFML/Graphics.hpp>
#include <utility>
#include "draw/IShape.h"
class MainWindow {
public:
    static MainWindow &getInstance() {
        static MainWindow instance;
        return instance;
    }
    void display();

    MainWindow(MainWindow const &) = delete;
    void operator=(MainWindow const &) = delete;

private:
    MainWindow(){
        window_.create(sf::VideoMode(1800, 1600), "FunGraph");
        x0_ = static_cast<float>(window_.getSize().x) / 2;
        y0_ = static_cast<float>(window_.getSize().y) / 2;
    }

    std::vector<std::unique_ptr<IShape>> shape_;
    sf::RenderWindow window_;
    int scale_ = 60;
    float x0_;
    float y0_;
public:
    void setShapes(const std::vector<std::unique_ptr<IShape>> &shapes);

    sf::RenderWindow &getWindow();

    void setScale(int sc);

    int getScale() const;

    float getX0() const;

    float getY0() const;

    void setX0(float x0);

    void setY0(float y0);

};


#endif //INC_2_GRAPH_H
