//
// Created by Alexey Lapin on 3/16/23.
//

#ifndef COMPLMATH2_UIEVENTS_H
#define COMPLMATH2_UIEVENTS_H

#include "MainWindow.h"
#include <SFML/Graphics.hpp>
struct UiEvents {
    explicit UiEvents(MainWindow &mainWindow) : mainWindow(mainWindow) {}
    void check(sf::Event event);
private:
    MainWindow &mainWindow;
};


#endif //COMPLMATH2_UIEVENTS_H
