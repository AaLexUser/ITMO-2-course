//
// Created by Alexey Lapin on 3/16/23.
//

#include <cmath>
#include "FuncGraph.h"

FuncGraph::FuncGraph(const std::function<double(double, std::vector<double>)> &f, const std::vector<double> &param, const double pointsPerSegment, sf::Color color)
    : f_(f), params_(param), pointsPerSegment_(pointsPerSegment), color_(color){
    left_ = -MainWindow::getInstance().getX0();
    right_ = static_cast<double>(MainWindow::getInstance().getWindow().getSize().x) + MainWindow::getInstance().getX0();
}

void FuncGraph::draw() {
    sf::VertexArray curve(sf::LineStrip, (right_ - left_ + 1) * pointsPerSegment_ );
    curve.setPrimitiveType(sf::PrimitiveType::LineStrip);
    for (int i = 0; i < (right_ - left_ + 1) * pointsPerSegment_; i++) {
        float x = left_ + i / pointsPerSegment_;
        float y = f_(x, params_);
        float x1 = MainWindow::getInstance().getX0() + x * MainWindow::getInstance().getScale();
        float y1 = MainWindow::getInstance().getY0() - y * MainWindow::getInstance().getScale();
        curve[i].position = sf::Vector2f(x1, y1);
        curve[i].color = sf::Color::Black;
    }
    // create the triangle strip array for the thick line
    sf::VertexArray thickLine(sf::TriangleStrip, curve.getVertexCount() * 2);
    float thickness = 5.f;
    // populate the triangle strip array with vertices
    for (int i = 0; i < curve.getVertexCount(); i++) {
        // calculate the direction of the line at each vertex
        sf::Vector2f direction;
        if (i == 0) {
            direction = curve[1].position - curve[0].position;
        }
        else if (i == curve.getVertexCount() - 1) {
            direction = curve[curve.getVertexCount() - 1].position - curve[curve.getVertexCount() - 2].position;
        }
        else {
            direction = (curve[i + 1].position - curve[i].position) + (curve[i].position - curve[i - 1].position);
        }

        // normalize the direction vector
        sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // calculate the perpendicular vector
        sf::Vector2f perpendicular(normalizedDirection.y, -normalizedDirection.x);

        // calculate the four vertices for the current line segment
        sf::Vector2f vertex1 = curve[i].position + perpendicular * thickness / 2.f;
        sf::Vector2f vertex2 = curve[i].position - perpendicular * thickness / 2.f;
        sf::Vector2f vertex3 = curve[i + 1].position + perpendicular * thickness / 2.f;
        sf::Vector2f vertex4 = curve[i + 1].position - perpendicular * thickness / 2.f;

        // populate the triangle strip array with the vertices
        thickLine[i * 2].position = vertex1;
        thickLine[i * 2 + 1].position = vertex2;
        thickLine[i * 2].color = color_;
        thickLine[i * 2 + 1].color = color_;
        thickLine[i * 2 + 2].position = vertex3;
        thickLine[i * 2 + 3].position = vertex4;
        thickLine[i * 2 + 2].color = color_;
        thickLine[i * 2 + 3].color = color_;
    }
    sf::RenderStates states;
    MainWindow::getInstance().getWindow().draw( thickLine, states);
}

std::unique_ptr<IShape> FuncGraph::clone() const {
    return std::make_unique<FuncGraph>(*this);
}
