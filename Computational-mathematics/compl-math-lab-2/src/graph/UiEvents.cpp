//
// Created by Alexey Lapin on 3/16/23.
//

#include "UiEvents.h"
#include <iostream>
using namespace sf;
void UiEvents::check(sf::Event event) {
    int scale = mainWindow.getScale();
    int x0 = mainWindow.getX0();
    int y0 = mainWindow.getY0();

    switch (event.type) {
        case Event::Closed:
            mainWindow.getWindow().close();
            break;
        case Event::MouseWheelMoved:
            if (event.mouseWheel.delta > 0) {
                scale+= event.mouseWheel.delta;
            }
            else if (event.mouseWheel.delta < 0) {
                scale = scale + event.mouseWheel.delta > 1 ? scale + event.mouseWheel.delta : 1;
            }
            break;
        case Event::KeyReleased:
            if (event.key.code == Keyboard::Up) {
                y0 += 10;
            }
            else if (event.key.code == Keyboard::Down) {
                y0 -= 10;
            }
            else if (event.key.code == Keyboard::Left) {
                x0 += 10;
            }
            else if (event.key.code == Keyboard::Right) {
                x0 -= 10;
            }
            else if (event.key.code == Keyboard::Escape) {
                x0 = mainWindow.getWindow().getSize().x / 2;
                y0 = mainWindow.getWindow().getSize().y/ 2;
                scale = 60;
            }
            else if (event.key.code == Keyboard::D){
                scale += 5;
            }
            else if (event.key.code == Keyboard::F){
                scale = scale - 5 > 0 ? scale - 5 : 0;
            }
            break;
        default:
            break;
    }
    mainWindow.setScale(scale);
    mainWindow.setX0(x0);
    mainWindow.setY0(y0);
}
