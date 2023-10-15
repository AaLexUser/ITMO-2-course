//
// Created by Alexey Lapin on 4/13/23.
//

#ifndef COMPLMATH4_MATRIX_H
#define COMPLMATH4_MATRIX_H

#include <vector>
template<typename Type, std::size_t Rows, std::size_t Cols>
class Matrix {
public:
    Matrix() = default;

// Constructor
    Matrix(std::initializer_list<std::vector<Type>> init) {
        std::size_t row = 0;
        for (auto& l : init) {
            std::size_t col = 0;
            for (auto& val : l) {
                if (col >= Cols) {
                    throw std::out_of_range("Column index out of range");
                }
                data[row][col] = val;
                ++col;
            }
            if (col != Cols) {
                throw std::invalid_argument("Invalid number of columns in row");
            }
            ++row;
            if (row > Rows) {
                throw std::out_of_range("Row index out of range");
            }
        }
        if (row != Rows) {
            throw std::invalid_argument("Invalid number of rows");
        }
    }
    explicit Matrix(std::vector<std::vector<Type>> init) {
        Matrix(init.begin(), init.end());
    }

    // Accessors
    const Type* operator[](std::size_t i) const {
        return data[i];
    }
    Type* operator[](std::size_t i) {
        return data[i];
    }

    // Operations
    Matrix<Type, Rows, Cols> operator+(const Matrix<Type, Rows, Cols>& rhs) const {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] + rhs[i][j];
            }
        }
        return result;
    }


    Matrix<Type, Rows, Cols> operator-(const Matrix<Type, Rows, Cols>& rhs) const {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] - rhs[i][j];
            }
        }
        return result;
    }
    Matrix<Type, Rows, Cols> operator-() const {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = -data[i][j];
            }
        }
        return result;
    }

    template<std::size_t Cols2>
    Matrix<Type, Rows, Cols2> operator*(const Matrix<Type, Cols, Cols2>& rhs) const {
        Matrix<Type, Rows, Cols2> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols2; ++j) {
                for (std::size_t k = 0; k < Cols; ++k) {
                    result[i][j] += data[i][k] * rhs[k][j];
                }
            }
        }
        return result;
    }

    Matrix<Type, Rows, Cols> operator*(const Type& rhs) const {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] * rhs;
            }
        }
        return result;
    }

    Matrix<Type, Rows, Cols> operator/(const Type& rhs) const {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] / rhs;
            }
        }
        return result;
    }

    Matrix<Type, Rows, Cols> T() {
        Matrix<Type, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[j][i];
            }
        }
        swap(result);
        return *this;
    }

    inline void swap(Matrix<Type, Rows, Cols>& other) noexcept {
        std::swap(data, other.data);
    };

    // Factory
    static Matrix<Type, Rows, Cols> make_matrix(std::initializer_list<std::vector<Type>> args) {
//        static_assert(static_cast<size_t>(args.size()) == static_cast<size_t>(Rows), "Invalid number of row vectors");
//        static_assert((static_cast<size_t>(args[0].size()) == static_cast<size_t>(Cols)) , "Invalid number of columns in vector");
        return Matrix<Type, Rows, Cols>(args);
    }

private:
    Type data[Rows][Cols] = {};
};


#endif //COMPLMATH4_MATRIX_H
