//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_LEGEND_H
#define COMPLMATH4_LEGEND_H


#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "IShape.h"
#include "../MainWindow.h"

class Legend : public IShape{
public:
    Legend() {
        font_.loadFromFile("/Users/aleksejlapin/CLionProjects/ComplMath4/Roboto/Roboto-Regular.ttf");
    }
    void addEntry(const std::string& label, const sf::Color& color) {
        entries_.emplace_back(label, color);
    }

    void clearEntries() {
        entries_.clear();
    }

    void draw() override;

    std::unique_ptr<IShape> clone() const override;

private:
    struct Entry {
        std::string label;
        sf::Color color;

        Entry(const std::string& l, const sf::Color& c) : label(l), color(c) {}
    };
    std::vector<Entry> entries_;
    sf::Font font_;
    unsigned int fontSize_ = 40;
    float textPadding_ = 5.f;
    float textSpacing_ = 50.f;
    float colorRectSize_ = 10.f;
};


#endif //COMPLMATH4_LEGEND_H
