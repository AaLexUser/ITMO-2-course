#include "MainWindow.h"
#include "UiEvents.h"


void MainWindow::display(){
    window_.setFramerateLimit(60);
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first fullscreen video mode
    bool isFullscreen = false;
    sf::Vector2u windowSize = window_.getSize();

    while (window_.isOpen())
    {
        sf::Event event{};
        UiEvents uiEvents(*this);

        while (window_.pollEvent(event))
        {
            uiEvents.check(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
            {
                isFullscreen = !isFullscreen; // Toggle fullscreen mode

                if (isFullscreen)
                {
                    windowSize = window_.getSize(); // Store the current window size before going fullscreen
                    window_.create(fullscreenMode, "FunGraph", sf::Style::Fullscreen); // Create the fullscreen window
                    x0_ = window_.getSize().x / 2;
                    y0_ = window_.getSize().y / 2;
                }
                else
                {
                    window_.create(sf::VideoMode(windowSize.x, windowSize.y), "FunGraph", sf::Style::Default); // Create the windowed window
                    x0_ = window_.getSize().x / 2;
                    y0_ = window_.getSize().y / 2;
                }
            }
        }

        window_.clear(sf::Color::White);
        for(auto &shape : shape_){
            shape->draw();
        }
        window_.display();
    }
}



int MainWindow::getScale() const {
    return scale_;
}

float MainWindow::getX0() const {
    return x0_;
}

float MainWindow::getY0() const {
    return y0_;
}

void MainWindow::setScale(int sc) {
    scale_ = sc;
}

void MainWindow::setX0(float x0) {
    MainWindow::x0_ = x0;
}

void MainWindow::setY0(float y0) {
    MainWindow::y0_ = y0;
}

sf::RenderWindow& MainWindow::getWindow() {
    return window_;
}

void MainWindow::setShapes(const std::vector<std::unique_ptr<IShape>> &shapes) {
    shape_.clear();
    for(auto &shape : shapes){
        shape_.push_back(std::move(shape->clone()));
    }
}


