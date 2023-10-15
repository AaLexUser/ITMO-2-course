//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_MATH_H
#define COMPLMATH5_MATH_H

#include <typeinfo>
#include <iostream>
#include <vector>
#include <type_traits>

class Math {
public:
    template<typename T>
    static T factorial(T num){
        static_assert(std::is_arithmetic<T>::value, "Must be a numeric type");
        T fact = 1;
        for(int i = 1; i <= num; ++i){
            fact*=i;
        }
        return fact;
    }

    template<typename T>
    static std::vector<T> createFactorial(T num){
        static_assert(std::is_arithmetic<T>::value, "Must be a numeric type");
        std::vector<T> fact(num+1);
        fact[0] = 1;
        for(int i = 1; i < fact.size(); ++i){
            fact[i] = fact[i-1]*i;
        }
        return fact;
    }

    template<typename T>
    static std::vector<std::vector<T>>& T(std::vector<std::vector<T>> & matrix){
        static_assert(std::is_arithmetic<T>::value, "Must be a numeric type");
        if(matrix.empty() || matrix[0].empty()){
            return matrix;
        }
        //static_assert(matrix.size() == matrix[0].size(), "Matrix must be a square matrix");
        std::vector<std::vector<T>> temp(matrix[0].size(), std::vector<T>(matrix.size()));
        for(int i = 0; i < matrix.size(); ++i){
            for(int j = 0; j < matrix[i].size(); ++j){
                temp[j][i] = matrix[i][j];
            }
        }
        std::swap(temp, matrix);
        return matrix;
    }

    static void calculateFinalDifferencesMatrix(const std::vector<std::pair<double, double>> & vec, std::vector<std::vector<double>> & res);
private:
    static std::vector<double> & calculateFinalDifferences(std::vector<double> & vec, int k);
};
extern Math math;


#endif //COMPLMATH5_MATH_H
