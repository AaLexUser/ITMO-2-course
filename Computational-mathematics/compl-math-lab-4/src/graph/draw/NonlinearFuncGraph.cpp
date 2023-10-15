//
// Created by Alexey Lapin on 3/21/23.
//

#include "NonlinearFuncGraph.h"
//plot a function graph of two variables z = f(x, y) or in other words a function graph in three-dimensional space (3D) in C++ and SFML. Write only one function that draw graph
#include <iostream>
NonlinearFuncGraph::NonlinearFuncGraph(double (*f)(double, double), double pointsPerSegment)
    : f_(f), pointsPerSegment_(pointsPerSegment) {
    leftX_ = -MainWindow::getInstance().getX0();
    rightX_ = MainWindow::getInstance().getX0();
    downY_ = -MainWindow::getInstance().getY0();
    upY_ = MainWindow::getInstance().getY0();

}
//plot a function graph of two variables z = f(x, y) or in other words a function graph in three-dimensional space (3D) in C++ and SFML. Write only one function that draw graph
void NonlinearFuncGraph::draw() {
    sf::VertexArray curve(sf::LineStrip, ((rightX_ - leftX_ + 1) * pointsPerSegment_)*((upY_ - downY_ + 1) * pointsPerSegment_) );
    curve.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sf::CircleShape circle(2.f);
    for (int i = 0; i < (rightX_ - leftX_ + 1) * pointsPerSegment_; i++) {
        for(int j = 0; j < (upY_ - downY_ + 1) * pointsPerSegment_; j++){
            float x = leftX_ + i / pointsPerSegment_;
            float y = downY_ + j / pointsPerSegment_;
            if( trunc(f_(x, y)*10) == 0){
                float x1 = MainWindow::getInstance().getX0() + x * MainWindow::getInstance().getScale();
                float y1 = MainWindow::getInstance().getY0() - y * MainWindow::getInstance().getScale();
//                curve[i].position = sf::Vector2f(x1, y1);
//                curve[i].color = sf::Color::Black;
                circle.setPosition(x1, y1);
                circle.setFillColor(sf::Color::Red);
                MainWindow::getInstance().getWindow().draw(circle);
            }
        }
        std::cout << i / ((rightX_ - leftX_ + 1) * pointsPerSegment_ )<< std::endl;
    }
//    // create the triangle strip array for the thick line
//    sf::VertexArray thickLine(sf::TriangleStrip, curve.getVertexCount() * 2);
//    float thickness = 5.f;
//    // populate the triangle strip array with vertices
//    for (int i = 0; i < curve.getVertexCount(); i++) {
//        // calculate the direction of the line at each vertex
//        sf::Vector2f direction;
//        if (i == 0) {
//            direction = curve[1].position - curve[0].position;
//        }
//        else if (i == curve.getVertexCount() - 1) {
//            direction = curve[curve.getVertexCount() - 1].position - curve[curve.getVertexCount() - 2].position;
//        }
//        else {
//            direction = (curve[i + 1].position - curve[i].position) + (curve[i].position - curve[i - 1].position);
//        }
//
//        // normalize the direction vector
//        sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//        // calculate the perpendicular vector
//        sf::Vector2f perpendicular(normalizedDirection.y, -normalizedDirection.x);
//
//        // calculate the four vertices for the current line segment
//        sf::Vector2f vertex1 = curve[i].position + perpendicular * thickness / 2.f;
//        sf::Vector2f vertex2 = curve[i].position - perpendicular * thickness / 2.f;
//        sf::Vector2f vertex3 = curve[i + 1].position + perpendicular * thickness / 2.f;
//        sf::Vector2f vertex4 = curve[i + 1].position - perpendicular * thickness / 2.f;
//
//        // populate the triangle strip array with the vertices
//        thickLine[i * 2].position = vertex1;
//        thickLine[i * 2 + 1].position = vertex2;
//        thickLine[i * 2].color = sf::Color::Red;
//        thickLine[i * 2 + 1].color = sf::Color::Red;
//        thickLine[i * 2 + 2].position = vertex3;
//        thickLine[i * 2 + 3].position = vertex4;
//        thickLine[i * 2 + 2].color = sf::Color::Red;
//        thickLine[i * 2 + 3].color = sf::Color::Red;
//    }
//    sf::RenderStates states;
//    MainWindow::getInstance().getWindow().draw( curve, states);
}

std::unique_ptr<IShape> NonlinearFuncGraph::clone() const {
    return std::make_unique<NonlinearFuncGraph>(*this);
}
