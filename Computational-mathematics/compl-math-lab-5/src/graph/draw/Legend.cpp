//
// Created by Alexey Lapin on 4/19/23.
//

#include "Legend.h"

void Legend::draw() {
    // Create a text object for each entry in the legend
    std::vector<sf::Text> texts;
    float textHeight = 13;
    float maxWidth = 1;
    for (int i = 0; i < entries_.size(); ++i) {
        sf::Text text(entries_[i].label, font_, fontSize_);
        text.setFillColor(sf::Color::Black);
//        text.setPosition(textPadding_, textPadding_ + i * (text.getGlobalBounds().height + textSpacing_));
        text.setPosition(textPadding_ + textHeight + textSpacing_, textPadding_ + i * (textHeight + textSpacing_));
        texts.push_back(text);
        maxWidth = std::max(maxWidth, 2*textPadding_ + textSpacing_ + textHeight+ text.getGlobalBounds().width);
    }

    // Draw a rectangle for the legend background
    sf::RectangleShape background(sf::Vector2f(maxWidth + 2 * textPadding_, texts.size() * (texts.front().getGlobalBounds().height + textSpacing_) + 2 * textPadding_));
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(1.f);
    MainWindow::getInstance().getWindow().draw(background);

    // Draw a colored rectangle for each entry in the legend
    float colorRectSizeX = maxWidth*0.3;
    float colorRectSizeY = textHeight + textSpacing_;
    for (int i = 0; i < entries_.size(); ++i) {
        sf::RectangleShape colorRect(sf::Vector2f(colorRectSizeY*0.5, colorRectSizeY*0.5));
        colorRect.setFillColor(entries_[i].color);
        colorRect.setPosition(textPadding_,  textPadding_ + i * (textHeight + textSpacing_) + textHeight*0.8 );
        MainWindow::getInstance().getWindow().draw(colorRect);
    }

    // Draw the text objects
    for (const auto& text : texts) {
        MainWindow::getInstance().getWindow().draw(text);
    }
}

std::unique_ptr<IShape> Legend::clone() const {
    return std::make_unique<Legend>(*this);
}
