//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_CHUNK_H
#define INC_71K2LEDEB_CHUNK_H

#include "delaunator.hpp"
#include "map/Perlin.h"
#include "map/Diamond.h"

class Chunk
{
public:
    double          _phi = 0.999985;
    unsigned int    _size;

public:
    explicit Chunk(unsigned int);
    Matrix<float>    generateMap(const glm::vec2 &,
                                 const Matrix<float> &, const Matrix<float> &,
                                 const Matrix<float> &, const Matrix<float> &);
    [[nodiscard]] std::vector<std::vector<bool>>    mapSimplify(const Matrix<float> &) const;

private:
    [[nodiscard]] double   calculateFlat(double, double, double, double, double, double, double, double) const;
    [[nodiscard]] double   calculatePyramid(double, double, double, double, double, double, double, double, double) const;
};

#endif //INC_71K2LEDEB_CHUNK_H
