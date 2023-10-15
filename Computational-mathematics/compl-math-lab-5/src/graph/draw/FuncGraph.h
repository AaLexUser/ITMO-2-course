//
// Created by Alexey Lapin on 3/16/23.
//

#ifndef COMPLMATH2_FUNCGRAPH_H
#define COMPLMATH2_FUNCGRAPH_H

#include "AbstractShape.h"
class FuncGraph : public AbstractShape{
    public:
        FuncGraph(const std::function<double(double, std::vector<double>)> &, const std::vector<double> &, const double, sf::Color color);
        void draw() override;
        [[nodiscard]] std::unique_ptr<IShape> clone() const override;
    private:
        const std::function<double(double, std::vector<double>)> & f_;
        const std::vector<double> & params_;
        double pointsPerSegment_;
        double left_;
        double right_;
        sf::Color color_;
};


#endif //COMPLMATH2_FUNCGRAPH_H
