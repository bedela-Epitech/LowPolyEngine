//
// Created by bedela on 11/04/2020.
//

#ifndef LOWPOLYENGINE_MATRIX_H
#define LOWPOLYENGINE_MATRIX_H

#include <iostream>
#include <vector>

template<class T>
class Matrix{
private:
    // row and/or colsize must be greater then 0;
    std::vector<T>  _matrix;
    unsigned int    _rowSize;
    unsigned int    _columnSize;

public:
    Matrix() {}

    Matrix(unsigned int rowSize, unsigned int colSize, T value)
            : _rowSize(rowSize),
              _columnSize(colSize)
    {
        if (!(rowSize > 0 && colSize > 0))
            throw std::logic_error("size not valid");
        _matrix = std::vector<T>(_rowSize * _columnSize, value);
    }

    Matrix(unsigned int rowSize, unsigned colSize, std::initializer_list<T> il)
            : _matrix(il),
              _rowSize(rowSize),
              _columnSize(colSize)
    {
        if (!(rowSize > 0 && colSize > 0))
            throw std::logic_error("size not valid");
        if (il.size() != _rowSize * _columnSize)
            throw std::logic_error("Wrong init list size");
    }

    // constructor by MVector
    // if the size of the vector is larger then the size of the matrix,
    // the matrix will construct with the first rowsize*colsize elements of the vector
    // if the size of the vector is smaller then the size of the matrix,
    // the matrix will not construct
    explicit Matrix(unsigned int rowSize, unsigned colSize, const std::vector<T> &vector)
            : _matrix(vector),
              _rowSize(rowSize),
              _columnSize(colSize)
    {
        if (!(rowSize > 0 && colSize > 0))
            throw std::logic_error("size not valid");
        if (_matrix.size() != _rowSize * _columnSize)
            throw std::logic_error("Wrong init list size");
    }

    // parameter pack constructor
    // constructs a matrix by typing values into the brackets
    // example: Matrix<int, 2, 2> a_matrix(1,2,3,4)
    // values can be of any type, they will be interpreted as of class T
    template<class ... N>
    explicit Matrix(unsigned int rowSize, unsigned colSize, T first, N&&... values)
            : _matrix{first, std::forward<T>(static_cast<T>(values))...},
              _rowSize(rowSize),
              _columnSize(colSize)
    {
        if (!(rowSize > 0 && colSize > 0))
            throw std::logic_error("size not valid");
        if (_matrix.size() != _rowSize * _columnSize)
            throw std::logic_error("Wrong init list size");
    }



// *******************************************************
    // Iterator support
// *******************************************************

    // traverse the entire vector
    typename std::vector<T>::iterator begin() {
        return _matrix.begin();
    }

    typename std::vector<T>::const_iterator begin()  const{
        return _matrix.begin();
    }

    typename std::vector<T>::iterator end() {
        return _matrix.end();
    }

    typename std::vector<T>::const_iterator end() const {
        return _matrix.end();
    }

    // returns the number of rows of the matrix
    [[nodiscard]] unsigned int rows() const{
        return _rowSize;
    }

    // returns the number of colums of the matrix
    [[nodiscard]] unsigned int cols() const{
        return _columnSize;
    }

    // returns the matrix as a vector
    std::vector<T>  &asVector() {
        return _matrix;
    }

    typename std::vector<T>::reference at(unsigned int raw, unsigned int col)
    {
        return _matrix.at(index(raw, col));
    }

    typename std::vector<T>::const_reference at(unsigned int raw, unsigned int col) const
    {
        return _matrix.at(index(raw, col));
    }
    // allows to access an element of the matrix by index expressed
    // in terms of rows and columns
    // @ param "r" - r'th row of the matrix
    // @ param "c" - c'th column of the matrix
    [[nodiscard]] unsigned int index(unsigned int r, unsigned int c) const {
        return r * cols() + c;
    }

    [[nodiscard]] bool    empty() const
    {
        return (_matrix.empty());
    }
};

#endif //LOWPOLYENGINE_MATRIX_H
