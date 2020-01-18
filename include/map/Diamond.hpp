

#ifndef _L_DIAMOND_HPP_
#define _L_DIAMOND_HPP_

#include "Mountain.h"
#include "Land.h"
#include <iostream>
#include <vector>

enum flag {NORMAL, RIGHT_END, BOTTOM_END};


class Diamond
{

public:
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;
    unsigned int							_size;
    std::vector<std::vector<float>>         _noiseMap;
    float							        _depth = 0;
    std::vector<std::vector<float>>	_map;

    std::vector<std::vector<float>>	_northMap;
    std::vector<std::vector<float>>	_eastMap;
    std::vector<std::vector<float>>	_southMap;
    std::vector<std::vector<float>>	_westMap;


private:
	float		    _height;
    std::mt19937    _gen;
public:
	Diamond(const float &, const unsigned int &,
	        const std::vector<std::vector<float>> &, const std::vector<std::vector<float>> &,
	        const std::vector<std::vector<float>> &, const std::vector<std::vector<float>> &,
	        const std::vector<std::vector<float>> &);

    void	manageSquare(unsigned int , unsigned int , const unsigned int, const std::shared_ptr<Biome> &);
    void	manageDiamond(unsigned int, unsigned int , const unsigned int, int, const std::shared_ptr<Biome> &);
	void	fillMap();
	void	printMap() const;

	float	boundedRand(float, float);

};


#endif // _L_DIAMOND_HPP_
