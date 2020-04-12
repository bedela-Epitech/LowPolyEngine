//
// Created by bedela on 11/04/2020.
//

#ifndef LOWPOLYENGINE_MATRIX_H
#define LOWPOLYENGINE_MATRIX_H

#include <iostream>
#include <vector>

template<class T>
class Matrix
{
private:

    // row and/or colsize must be greater then 0;
    std::vector<T>  _matrix;
    unsigned int    _rowSize;
    unsigned int    _columnSize;

public:
    ////////////////////////
    //                    //
    //    CONSTRUCTORS    //
    //                    //
    ////////////////////////
    Matrix() {}

    // Init the matrix size rowSize * colSize with the given value
    Matrix(unsigned int rowSize, unsigned int colSize, T value)
            : _rowSize(rowSize),
              _columnSize(colSize)
    {
        if (!(rowSize > 0 && colSize > 0))
            throw std::logic_error("size not valid");
        _matrix = std::vector<T>(_rowSize * _columnSize, value);
    }

    // init the matrix with the given init list
    // check that init list size matches rowSize * colSize
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

    // init the matrix with the given vector
    // check that vector's size matches rowSize * colSize
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

    // init the matrix with the given arguments
    // check that the number of arguments matches rowSize * colSize
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

    ///////////////////////////////////////
    //                                   //
    //    VECTOR FUNCTION REPLICATION    //
    //                                   //
    ///////////////////////////////////////

    // return the begin iterator of the internal vector
    typename std::vector<T>::iterator begin() {
        return _matrix.begin();
    }

    // return the begin iterator of the internal vector
    typename std::vector<T>::const_iterator begin()  const{
        return _matrix.begin();
    }

    // return the end iterator of the internal vector
    typename std::vector<T>::iterator end() {
        return _matrix.end();
    }

    // return the end iterator of the internal vector
    typename std::vector<T>::const_iterator end() const {
        return _matrix.end();
    }

    // With a vector of vector, we would access like that :
    // auto value = myVectorOfVector[row][col]
    // here we access the same value with :
    // auto value = Matrix.at(row, col)
    // the major difference here is that we have only one vector
    // internaly, leads to better memory optimisation


    // return the element at the raw/col position
    typename std::vector<T>::reference at(unsigned int raw, unsigned int col)
    {
        return _matrix.at(index(raw, col));
    }

    // return the element at the raw/col position
    typename std::vector<T>::const_reference at(unsigned int raw, unsigned int col) const
    {
        return _matrix.at(index(raw, col));
    }

    // check if internal vector is empty
    [[nodiscard]] bool    empty() const
    {
        return (_matrix.empty());
    }


    ///////////////////////
    //                   //
    //      GETTERS      //
    //                   //
    ///////////////////////

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

    // allows to access an element of the matrix by index
    [[nodiscard]] unsigned int index(unsigned int row, unsigned int col) const {
        return row * cols() + col;
    }
};

#endif //LOWPOLYENGINE_MATRIX_H
