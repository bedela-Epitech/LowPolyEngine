//
// Created by adrien on 03/01/20.
//

#ifndef _L_DIAMOND_H_
#define _L_DIAMOND_H_

#include "Mountain.h"
#include "Land.h"
#include "encapsulation/Matrix.h"
#include <iostream>


enum flag {NORMAL, RIGHT_END, TOP_END};

class Diamond
{
public:
    Matrix<float> _map;

private:
	float		    _height = 0.55f;
    unsigned int    _size;
    std::mt19937    _gen;

    bool    _northMapEmpty;
    bool    _eastMapEmpty;
    bool    _southMapEmpty;
    bool    _westMapEmpty;

public:
	Diamond(unsigned int,
	        const Matrix<float> &, const Matrix<float> &,
	        const Matrix<float> &, const Matrix<float> &);
    void	fillMap();
    void	printMap() const;

private:
    void	manageSquare(unsigned int , unsigned int , unsigned int, const std::shared_ptr<Biome> &);
    void	manageDiamond(unsigned int, unsigned int , unsigned int, int, const std::shared_ptr<Biome> &);
	[[nodiscard]] float getDiff(int, int, unsigned int) const;
	[[nodiscard]] float	boundedRand(float, float);

};

#endif // _L_DIAMOND_H_
