//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_APPROXIMATIONMANAGER_H
#define COMPLMATH4_APPROXIMATIONMANAGER_H


#include <vector>
#include "IApproximation.h"
#include "impl/Linear.h"
#include "ApproximationEnum.h"
#include "impl/Quadratic.h"
#include "impl/Cubic.h"
#include "impl/Exponential.h"
#include "impl/Logarithmic.h"
#include "impl/Power.h"

class ApproximationManager {
public:


    ApproximationManager(std::vector<std::pair<double, double>> points){
        approximations_[ApproximationEnum::Linear] = std::make_unique<approx::Linear>(points);
        approximations_[ApproximationEnum::Quadratic] = std::make_unique<approx::Quadratic>(points);
        approximations_[ApproximationEnum::Cubic] = std::make_unique<approx::Cubic>(points);
        approximations_[ApproximationEnum::Exponential] = std::make_unique<approx::Exponential>(points);
        approximations_[ApproximationEnum::Logarithmic] = std::make_unique<approx::Logarithmic>(points);
        approximations_[ApproximationEnum::Power] = std::make_unique<approx::Power>(points);
    }
    std::unique_ptr<approx::IApproximation> operator[](ApproximationEnum key){
        return std::move(approximations_[key]);
    }

    const std::unordered_map<ApproximationEnum, std::unique_ptr<approx::IApproximation>> & getApproximations() const{
        return approximations_;
    }


private:
    std::unordered_map<ApproximationEnum, std::unique_ptr<approx::IApproximation>> approximations_;

};


#endif //COMPLMATH4_APPROXIMATIONMANAGER_H
